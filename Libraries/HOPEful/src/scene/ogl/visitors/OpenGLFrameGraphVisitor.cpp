#include <scene/ogl/visitors/OpenGLFrameGraphVisitor.hpp>
#include <scene/framegraph/ActiveCameraNode.hpp>
#include <scene/framegraph/ClearBuffersNode.hpp>
#include <scene/framegraph/FrustumCullingNode.hpp>
#include <scene/framegraph/RenderCapabilityNode.hpp>
#include <scene/framegraph/RenderPassSelectorNode.hpp>
#include <scene/framegraph/ViewportNode.hpp>
#include <scene/framegraph/MemoryBarrierNode.hpp>
#include <scene/framegraph/deferred/offscreen/base/AbstractFramebufferRenderNode.hpp>
#include <scene/framegraph/deferred/offscreen/base/LayerFramebufferRenderNode.hpp>
#include <scene/framegraph/deferred/offscreen/OffscreenRenderingNode.hpp>
#include <scene/framegraph/deferred/subtree/ShadingStepNode.hpp>
#include <scene/framegraph/deferred/effects/shadows/DirectionalLightShadowNode.hpp>
#include <scene/framegraph/deferred/effects/fog/FogRenderNode.hpp>
#include <scene/framegraph/deferred/effects/EffectApplierNode.hpp>
#include <scene/components/RenderConfiguration.hpp>
#include <Math.hpp>
#include <GLFW/glfw3.h>
#include <HopeAPI.hpp>

using namespace Hope ;
using namespace Hope::GL ;

OpenGLFrameGraphVisitor::OpenGLFrameGraphVisitor(Framebuffer* defaultFramebuffer)
    : IFrameGraphVisitor() {
    m_aggregators.push_back(FrameGraphBranchState()) ;
    m_renderer.setDefaultFramebuffer(defaultFramebuffer) ;
}

void OpenGLFrameGraphVisitor::setSceneRoot(Hope::Transform* root) {
    m_sceneRoot = root ;
}

void OpenGLFrameGraphVisitor::visit(ActiveCameraNode* node) {
    m_aggregators.back().setActiveCameraNode(node) ;

    // TODO: Compute eye position in world space on camera attach!
	auto cameraEntity = node -> camera() -> firstEntity() ;
    Mind::Vector3f position = (cameraEntity -> transform()).translation() ;
    m_renderer.baseUBO().setEyePosition(position) ;

    if (node -> cacheEmpty()) {
        // Parse the scene graph.
        assert(m_aggregators.size() > 0) ;
        Hope::ProcessedSceneNode rootNode ;
        rootNode.node = m_sceneRoot ;
        rootNode.worldMatrix = m_sceneRoot -> world() ;
        m_processedNodes.push(rootNode) ;

        while (m_processedNodes.size() > 0) {
            // For each entity: check if all the conditions are OK otherwise, go
            // back to the parent entity and process the other ones.
            // The children of an invalid entity are discarded as well.
            parseSceneGraph() ;
        }
    }
}

void OpenGLFrameGraphVisitor::visit(ClearBuffersNode* node) {
    BufferClearer::Clear(node -> buffers()) ;
}

void OpenGLFrameGraphVisitor::visit(FrustumCullingNode* /*node*/) {
    // TODO
}

void OpenGLFrameGraphVisitor::visit(DirectionalLightShadowNode* node) {
    if (!m_projectionData.initialized) {
        return ;
    }

    // Compute the position of the ShadowCam to fit the rendering camera
    // frustum.
    const float AspectRatio = m_projectionData.absoluteAreaWidth / m_projectionData.absoluteAreaHeight ;
    node -> computeCascadeShadowMaps(AspectRatio) ;

    // Adjust the viewport size to fit the resolution of the shadow map.
    uint32_t resolution = node -> resolution() ;
    glViewport(0, 0, resolution, resolution) ;

    // Notify that the viewport has been modified...
    m_projectionData.lastViewport = nullptr ;
    m_globalEffects.push_back(node -> data()) ;
}

void OpenGLFrameGraphVisitor::visit(AbstractFramebufferRenderNode* node) {
    m_aggregators.back().setFramebufferRenderNode(node) ;

    // Resize the framebuffer textures with the window if needed.
    if (m_hasWindowChanged && node -> windowSize()) {
        (node -> framebuffer()) -> resize(m_windowSize) ;
    }

    (node -> framebuffer()) -> bind() ;
}

void OpenGLFrameGraphVisitor::visit(LayerFramebufferRenderNode* node) {
    // Resize the framebuffer textures with the window if needed.
    if (m_hasWindowChanged && node -> windowSize()) {
        Framebuffer2DStack* framebuffer = node -> framebuffer() ;
        framebuffer -> resize(m_windowSize) ;
    }

    (node -> framebuffer()) -> bind() ;
    (node -> framebuffer()) -> bindDepthLayer(node -> layer()) ;
}

void OpenGLFrameGraphVisitor::visit(OffscreenRenderingNode* node) {
    m_aggregators.back().setRenderAtEnd(node -> renderingStepEnabled()) ;

    m_aggregators.back().applyRenderCapabilities() ;
    m_renderer.deferredShading(
        node -> material(),
        m_aggregators.back().memoryBarrier(),
        m_aggregators.back().effectData()
    ) ;
    m_aggregators.back().removeRenderCapabilities() ;
}

void OpenGLFrameGraphVisitor::visit(ShadingStepNode* node) {
    m_aggregators.back().setRenderAtEnd(node -> renderingStepEnabled()) ;

    // Merge global effects.
    m_aggregators.back().addEffectData(m_globalEffects) ;

    m_aggregators.back().applyRenderCapabilities() ;
    m_renderer.deferredShading(
        node -> material(),
        m_aggregators.back().memoryBarrier(),
        m_aggregators.back().effectData()
    ) ;
    m_aggregators.back().removeRenderCapabilities() ;
}

void OpenGLFrameGraphVisitor::visit(RenderPassSelectorNode* node) {
    m_aggregators.back().setRenderPassID(node -> passID()) ;
}

void OpenGLFrameGraphVisitor::visit(ViewportNode* node) {
    bool offscreenRender = m_renderer.defaultFramebuffer() != nullptr ;

    if (!m_hasWindowChanged
            && !offscreenRender
            && (m_projectionData.lastViewport == node)
       ) {
        return ;
    }

    m_projectionData.lastViewport = node ;

    Mind::Point2Df relativePosition = node -> position() ;
    Mind::Dimension2Df relativeDimension = node -> dimension() ;

    unsigned int fboWidth = 0 ;
    unsigned int fboHeight = 0 ;

    if (offscreenRender) {
        fboWidth = m_renderer.defaultFramebuffer() -> width() ;
        fboHeight = m_renderer.defaultFramebuffer() -> height() ;
    }
    else {
        fboWidth = m_windowSize.width() ;
        fboHeight = m_windowSize.height() ;
    }

    Mind::Point2Df absolutePosition(
        relativePosition.get(Mind::Point2Df::X) * fboWidth,
        relativePosition.get(Mind::Point2Df::Y) * fboHeight
    ) ;

    m_projectionData.absoluteAreaWidth = relativeDimension.width() * fboWidth ;
    m_projectionData.absoluteAreaHeight = relativeDimension.height() * fboHeight ;

    // Apply the viewport parameters.
    glViewport(
        static_cast<int>(absolutePosition.get(Mind::Point2Df::X)),
        static_cast<int>(absolutePosition.get(Mind::Point2Df::Y)),
        static_cast<int>(m_projectionData.absoluteAreaWidth),
        static_cast<int>(m_projectionData.absoluteAreaHeight)
    ) ;

    // Compute the viewport matrices.
    Mind::Scalar viewportX = relativePosition.get(Mind::Point2Df::X) ;
    Mind::Scalar viewportY = relativePosition.get(Mind::Point2Df::Y) ;
    Mind::Scalar viewportWidth = relativeDimension.width() ;
    Mind::Scalar viewportHeight = relativeDimension.height() ;
    Mind::Point3Df row0(viewportWidth / 2.f, 0.f, viewportWidth / (2 + viewportX)) ;
    Mind::Point3Df row1(0.f, viewportHeight/ 2.f, viewportHeight / (2 + viewportY)) ;
    Mind::Point3Df row2(0.f, 0.f, 1.f) ;

    Mind::Matrix4x4f viewportMatrix ;
    viewportMatrix.setRowValues(0, row0) ;
    viewportMatrix.setRowValues(1, row1) ;
    viewportMatrix.setRowValues(2, row2) ;

    Mind::Matrix4x4f inverseViewportMatrix ;
    viewportMatrix.inverse(inverseViewportMatrix) ;

    Mind::Vector2f viewportSize(m_projectionData.absoluteAreaWidth, m_projectionData.absoluteAreaHeight) ;
    m_renderer.baseUBO().setViewportSize(viewportSize) ;
    m_renderer.baseUBO().setViewportMatrix(viewportMatrix) ;
    m_renderer.baseUBO().setInverseViewportMatrix(inverseViewportMatrix) ;

    m_projectionData.initialized = true ;
}

void OpenGLFrameGraphVisitor::visit(MemoryBarrierNode* node) {
    m_aggregators.back().setMemoryBarrier(node -> bits()) ;
}

void OpenGLFrameGraphVisitor::visit(RenderCapabilityNode* node) {
    m_aggregators.back().addRenderCapabilities(node) ;
}

void OpenGLFrameGraphVisitor::visit(EffectApplierNode* node) {
    m_aggregators.back().addEffectData({ node -> effect() }) ;
}

void OpenGLFrameGraphVisitor::visit(FogRenderNode* node) {
    m_globalEffects.push_back(node -> data()) ;
}

void OpenGLFrameGraphVisitor::makeRender() {
    FrameGraphBranchState& state = m_aggregators.back() ;

    if (!state.renderAtEnd() || state.activeCamera() == nullptr) {
        // Remove the last RenderConditionAggregator from the list!
        m_aggregators.pop_back() ;

        // Prevent rendering.
        return ;
    }

    updateCameraSettings() ;

    const std::shared_ptr<Hope::FrameRenderCache> cache = state.activeCameraCache() ;
    // Send data of the base UBO to the GPU before rendering this part of the
    // framegraph.
    m_renderer.updateLightUBO(cache) ;
    m_renderer.baseUBO().update() ;

    // Render the frame.
    m_aggregators.back().applyRenderCapabilities() ;
    m_renderer.render(
        state.renderPassID(),
        cache -> meshes(),
        m_aggregators.back().memoryBarrier()
    ) ;
    m_aggregators.back().removeRenderCapabilities() ;

    // Remove the last RenderConditionAggregator from the list!
    m_aggregators.pop_back() ;
}

void OpenGLFrameGraphVisitor::parseSceneGraph() {
	Hope::Transform* processedTransform = m_processedNodes.top().node ;
    Hope::Entity* renderedEntity = processedTransform -> entity() ;
    FrameGraphBranchState& state = m_aggregators.back() ;

    if (renderedEntity && state.conditions().check(renderedEntity)) {
        // Save the world matrix before pop.
        Mind::Matrix4x4f currentWorldMatrix = m_processedNodes.top().worldMatrix ;

        state.activeCameraCache() -> cacheEntity(
            renderedEntity,
            currentWorldMatrix
        ) ;

        // As the top node is processed, pop it from the stack.
        m_processedNodes.pop() ;

        // If the node has children, push them in the stack.
        const std::vector<Node*>& nodeChildren = processedTransform -> children() ;
        for (const Hope::Node* child : nodeChildren) {
            const Hope::Transform* childTransformConst = static_cast<const Transform*>(child) ;
            Hope::ProcessedSceneNode childNode ;
            childNode.node = const_cast<Transform*>(childTransformConst) ;
            childNode.worldMatrix = childNode.node -> world() ;
            m_processedNodes.push(childNode) ;
        }
    }
}

void OpenGLFrameGraphVisitor::updateCameraSettings() {
    FrameGraphBranchState& state = m_aggregators.back() ;
    Hope::CameraComponent* camera = state.activeCamera() -> camera() ;

    // For cameras that require minimal data, just update them.
    if (!(camera -> requireFullDataUpdate())) {
        // Set up the projection matrix.
        static const float UnusedAspectRatio = 0.f ;
        Mind::Matrix4x4f projectionMatrix ;
        camera -> projectionMatrix(projectionMatrix, UnusedAspectRatio) ;
        m_renderer.baseUBO().setProjectionMatrix(projectionMatrix) ;
        m_renderer.setProjectionMatrix(projectionMatrix) ;

        // Update the view matrix.
        const Mind::Matrix4x4f& viewMatrix = camera -> viewMatrix() ;
        m_renderer.baseUBO().setViewMatrix(viewMatrix) ;
        m_renderer.setViewMatrix(viewMatrix) ;

        return ;
    }

    // Otherwise, proceed to a full update.
    const Hope::AbstractFramebufferRenderNode* offscreen = state.offScreenRender() ;
    camera -> update() ;

    // Set up the clear color.
    const Color& clearColor = camera -> clearColor() ;
    glClearColor(
        clearColor.red(),
        clearColor.green(),
        clearColor.blue(),
        clearColor.alpha()
    ) ;

    float aspectRatio = 0.f ;
    // Update the projection matrix.
    if (!offscreen || offscreen -> windowSize()) {
        aspectRatio = m_projectionData.absoluteAreaWidth / m_projectionData.absoluteAreaHeight ;
    }
    else {
        const Framebuffer* offscreenFramebuffer = offscreen -> framebuffer() ;
        float width = static_cast<float>(offscreenFramebuffer -> width()) ;
        float height = static_cast<float>(offscreenFramebuffer -> height()) ;
        aspectRatio = width / height ;
    }

    Mind::Matrix4x4f projectionMatrix ;
    // Set up the projection matrix.
    camera -> projectionMatrix(projectionMatrix, aspectRatio) ;
    Mind::Matrix4x4f inverseProjectionMatrix ;
    projectionMatrix.inverse(inverseProjectionMatrix) ;

    m_renderer.baseUBO().setProjectionMatrix(projectionMatrix) ;
    m_renderer.baseUBO().setInverseProjectionMatrix(inverseProjectionMatrix) ;
    m_renderer.baseUBO().setAspectRatio(aspectRatio) ;
    m_renderer.setProjectionMatrix(projectionMatrix) ;

    // Update the view matrix.
    const Mind::Matrix4x4f& viewMatrix = camera -> viewMatrix() ;

    // Update the required data.
    m_renderer.setViewMatrix(viewMatrix) ;
    m_renderer.baseUBO().setFieldOfView(camera -> fov()) ;
    m_renderer.baseUBO().setNearPlaneDistance(camera -> nearPlaneDistance()) ;
    m_renderer.baseUBO().setFarPlaneDistance(camera -> farPlaneDistance()) ;
    m_renderer.baseUBO().setTime(static_cast<float>(glfwGetTime())) ;
    m_renderer.baseUBO().setViewMatrix(viewMatrix) ;

    Mind::Matrix4x4f resultInverse ;
    viewMatrix.inverse(resultInverse) ;
    m_renderer.baseUBO().setInverseViewMatrix(resultInverse) ;

    Mind::Matrix4x4f viewProjectionMatrix = projectionMatrix * viewMatrix ;
    m_renderer.baseUBO().setViewProjectionMatrix(viewProjectionMatrix) ;

    viewProjectionMatrix.inverse(resultInverse) ;
    m_renderer.baseUBO().setInverseViewProjectionMatrix(resultInverse) ;
}
