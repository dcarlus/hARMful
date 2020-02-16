#ifndef __HOPE__FRAMEBUFFER_RENDER__
#define __HOPE__FRAMEBUFFER_RENDER__

#include <scene/framegraph/deferred/offscreen/base/AbstractFramebufferRenderNode.hpp>
#include <scene/SceneTypes.hpp>
#include <memory>

#ifdef OGL
    #include <scene/ogl/rendering/framebuffers/Framebuffer2D.hpp>
#endif

namespace Hope {
    /**
     * Node to use a framebuffer.
     */
    class FramebufferRenderNode : public AbstractFramebufferRenderNode {
        private:
            /**
             * The underlying framebuffer to perform off-screen rendering.
             */
            std::shared_ptr<API::Framebuffer2D> m_framebuffer = nullptr ;

        public:
            /**
             * Create a new FramebufferRenderNode instance.
             * @param   size        Size of the framebuffer.
             * @param   windowSize  If true, the size of the framebuffer follows
             *                      the size of the window. If false, the size
             *                      of the framebuffer is fixed.
             */
            FramebufferRenderNode(
                const Mind::Dimension2Di& size,
                const bool windowSize,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Create a new FramebufferRenderNode instance to edit the content of
             * an existing framebuffer.
             * @param   other   Other OffScreenRenderNode to edit framebuffer.
             */
            FramebufferRenderNode(
                FramebufferRenderNode* other,
                FrameGraphNode* parent
            ) ;

            /**
             * Get the framebuffer.
             */
            API::Framebuffer* framebuffer() override {
                return m_framebuffer.get() ;
            }

            /**
             * Get the framebuffer.
             */
            const API::Framebuffer* framebuffer() const override {
                return m_framebuffer.get() ;
            }
    } ;
}

#endif