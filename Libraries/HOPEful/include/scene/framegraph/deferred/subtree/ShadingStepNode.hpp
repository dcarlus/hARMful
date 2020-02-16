#ifndef __HOPE__SHADING_STEP_NODE__
#define __HOPE__SHADING_STEP_NODE__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/framebuffers/Framebuffer.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/FrameGraphNode.hpp>
#include <scene/framegraph/deferred/offscreen/GBufferRenderNode.hpp>
#include <scene/framegraph/deferred/offscreen/OffscreenRenderingNode.hpp>
#include <memory>

namespace Hope {
    /**
     * Framegraph node that is used to compute and render the result of shading
     * from a G-Buffer.
     *
     * @warning A GBuffer must have been created and rendered into before
     *          putting this node in the framegraph!
     */
    class ShadingStepNode final : public OffscreenRenderingNode {
        public:
            static const unsigned char ShadingRenderTarget = 0 ;

        private:
            /**
             * Framebuffer in which shading is computed.
             */
            API::Framebuffer* m_shadingFBO = nullptr ;

        public:
            /**
             * Create a new ShadingStepNode instance.
             * @param   gBuffer G-Buffer used for the deferred shading.
             */
            ShadingStepNode(
                GBufferRenderNode* gBuffer,
                API::Framebuffer* shadingFBO,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Destruction of the ShadingStepNode instance.
             */
            virtual ~ShadingStepNode() ;

            // Remove copy/move operations.
            ShadingStepNode(const ShadingStepNode& copied) = delete;
            ShadingStepNode(ShadingStepNode&& moved) = delete;
            ShadingStepNode& operator=(const ShadingStepNode& copied) = delete;
            ShadingStepNode& operator=(ShadingStepNode&& moved) = delete;

        protected:
            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) ;
    } ;
}

#endif