#ifndef __HOPE__GL_FRAMEBUFFER__
#define __HOPE__GL_FRAMEBUFFER__

#include <HopeAPI.hpp>
#include <utils/Platform.hpp>

#include <scene/ogl/GLDefines.hpp>
#include <scene/ogl/textures/Texture.hpp>
#include <scene/ogl/textures/environment/EnvironmentMapTexture.hpp>
#include <scene/ogl/textures/formats/InternalFormats.hpp>
#include <scene/ogl/textures/formats/PixelFormats.hpp>
#include <scene/ogl/textures/formats/PixelDataTypes.hpp>
#include <geometry/dimensions/Dimension2Di.hpp>
#include <geometry/dimensions/Dimension2Df.hpp>
#include <list>
#include <memory>
#include <vector>

namespace Hope::GL {
    /**
     * Memory buffer that contains a complete frame of data.
     * This allows off-screen rendering for several tasks: mirrors in a 3D
     * scene, deferred rendering, etc.
     */
    class Framebuffer {
        public:
            /**
             * Access mode to the framebuffer.
             */
            enum AccessMode : GLenum {
                ReadOnly = GL_READ_FRAMEBUFFER,
                WriteOnly = GL_DRAW_FRAMEBUFFER,
                ReadWrite = GL_FRAMEBUFFER
            } ;

        protected:
            /**
             * To know if mipmaps are automatically generated. Here, no.
             */
            static const bool GenerateMipmaps ;

            /**
             * Mipmap level for the attached textures.
             */
            static const int MipmapLevel = 0 ;

        private:
            /**
             * ID of the framebuffer object on GPU side.
             */
            GLuint m_fboID = INVALID_VALUE ;

        public:
            /**
             * Create a new Framebuffer instance.
             */
            exported Framebuffer() ;

            /**
             * Create a new Framebuffer instance with a predefined size.
             * @param   size    Size of the framebuffer attachments in pixels.
             */
            exported Framebuffer(const Mind::Dimension2Di& size) ;

            /**
             * Destruction of the Framebuffer.
             */
            exported virtual ~Framebuffer() ;

            /**
             * Get the ID of the current Framebuffer.
             */
            exported GLuint id() const {
                return m_fboID ;
            }

            /**
             * Resize the framebuffer.
             * @param   newSize Size of the framebuffer attachments in pixels.
             */
            exported virtual void resize(const Mind::Dimension2Di& newSize) = 0 ;

            /**
             * Bind the framebuffer.
             */
            exported void bind(const AccessMode mode = AccessMode::ReadWrite) const {
                glBindFramebuffer(mode, m_fboID) ;
            }

            /**
             * Unbind the framebuffer.
             */
            exported void unbind(const AccessMode mode = AccessMode::ReadWrite) const {
                glBindFramebuffer(mode, 0) ;
            }

            /**
             * Set the read buffer.
             */
            exported void setReadBuffer(const unsigned char index) ;

            /**
             * Unset the read buffer.
             */
            exported void unsetReadBuffer() ;

            /**
             * Set the color attachments to use.
             * @param   indices List of the attachment indices to use.
             */
            exported void setDrawBuffers(const std::list<unsigned char>& indices) ;

            /**
             * Indicate that the framebuffer does not use any color attachment.
             */
            exported void useNoColorBuffers() ;

            /**
             * Attach a color texture to the framebuffer.
             * The texture is internally generated and managed.
             * Notice that several textures can be attached to a same
             * framebuffer in order to perform multiple render target
             * operations.
             * @param   attachmentIndex Index of the attachment point to the
             *                          framebuffer. Starts at 0, you can get
             *                          the amount of color attachment with the
             *                          GetColorAttachmentCount() method.
             * @param   internalFormat  Number of color components in the
             *                          texture.
             * @param   pixelDataFormat Pixel format of the attached texture.
             * @param   pixelDataType   Type of the pixels data.
             */
            exported virtual void attachColor(
                const unsigned char attachmentIndex,
                const InternalFormat internalFormat,
                const PixelFormat pixelDataFormat,
                const PixelDataType pixelDataType
            ) = 0 ;

            /**
             * Attach an external color texture to the framebuffer.
             * Notice that several textures can be attached to a same
             * framebuffer in order to perform multiple render target
             * operations.
             * @param   attachmentIndex Index of the attachment point to the
             *                          framebuffer. Starts at 0, you can get
             *                          the amount of color attachment with the
             *                          GetColorAttachmentCount() method.
             * @param   texture         The external texture to attach to the
             *                          framebuffer.
             */
            exported virtual void attachColor(
                const unsigned char attachmentIndex,
                const Texture* texture
            ) = 0 ;

            /**
             * Attach an external color texture to the framebuffer from a
             * cubemap.
             * Notice that several textures can be attached to a same
             * framebuffer in order to perform multiple render target
             * operations.
             * @param   attachmentIndex Index of the attachment point to the
             *                          framebuffer. Starts at 0, you can get
             *                          the amount of color attachment with the
             *                          GetColorAttachmentCount() method.
             * @param   texture         The external texture to attach to the
             *                          framebuffer.
             * @param   faceIndex       Index of the face in the cubemap
             */
            exported void attachCubeColor(
                const unsigned char attachmentIndex,
                const EnvironmentMapTexture* texture,
                const CubeFace faceIndex
            ) ;

            /**
             * Attach the depth buffer.
             */
            exported virtual void attachDepth() = 0 ;

            /**
             * Attach the depth buffer.
             * @param   texture         The external texture to attach to the
             *                          framebuffer.
             */
            exported virtual void attachDepth(const Texture* texture) = 0 ;

            /**
             * Attach the stencil buffer.
             */
            exported virtual void attachStencil() = 0 ;

            /**
             * Attach the stencil buffer.
             * @param   texture         The external texture to attach to the
             *                          framebuffer.
             */
            exported virtual void attachStencil(const Texture* texture) = 0 ;

            /**
             * Attach the combination of depth+stencil buffer.
             */
            exported virtual void attachDepthStencil() = 0 ;

            /**
             * Attach the combination of depth+stencil buffer.
             * @param   texture         The external texture to attach to the
             *                          framebuffer.
             */
            exported virtual void attachDepthStencil(const Texture* texture) = 0 ;

            /**
             * Bind the color attachment.
             */
            exported virtual void bindUnitColor(const unsigned char attachmentIndex) const = 0 ;

            /**
             * Bind the depth attachment.
             */
            exported virtual void bindUnitDepth(const unsigned char unit) const = 0 ;

            /**
             * Bind the stencil attachment.
             */
            exported virtual void bindUnitStencil(const unsigned char unit) const = 0 ;

            /**
             * Bind the depth+stencil attachment.
             */
            exported virtual void bindUnitDepthStencil(const unsigned char unit) const = 0 ;


            /**
             * Unbind the color attachment.
             */
            exported virtual void unbindUnitColor(const unsigned char attachmentIndex) const = 0 ;

            /**
             * Unbind the depth attachment.
             */
            exported virtual void unbindUnitDepth(const unsigned char unit) const = 0 ;

            /**
             * Unbind the stencil attachment.
             */
            exported virtual void unbindUnitStencil(const unsigned char unit) const = 0 ;

            /**
             * Unbind the depth+stencil attachment.
             */
            exported virtual void unbindUnitDepthStencil(const unsigned char unit) const = 0 ;


            /**
             * Detach a texture from the framebuffer.
             * @param   attachment      Attachment point to the framebuffer.
             */
            exported void detachColor(const int attachmentIndex) ;

            /**
             * Detach the depth buffer.
             */
            exported void detachDepth() ;

            /**
             * Detach the stencil buffer.
             */
            exported void detachStencil() ;

            /**
             * Detach the combination of depth+stencil buffer.
             */
            exported void detachDepthStencil() ;

            /**
             * Get the wanted color attachment.
             * @param   attachmentIndex Attachment index.
             */
            exported virtual const Texture* colorAttachment(const unsigned char attachmentIndex) const = 0 ;

            /**
             * Get the depth attachment.
             */
            exported virtual const Texture* depthAttachment() const = 0 ;

            /**
             * Get the stencil attachment.
             */
            exported virtual const Texture* stencilAttachment() const = 0 ;

            /**
             * Get the depth & stencil attachment.
             */
            exported virtual const Texture* depthStencilAttachment() const = 0 ;

            /**
             * Check the status of the framebuffer.
             * @return  true if the framebuffer is complete; false otherwise.
             *          In case the framebuffer is not complete, a log message
             *          is registered.
             */
            exported bool isComplete() const ;

            /**
             * Get the framebuffer width.
             */
            exported virtual int width() const = 0 ;

            /**
             * Get the framebuffer height.
             */
            exported virtual int height() const = 0 ;

            /**
             * Get the amount of color attachments.
             */
            exported static GLint GetColorAttachmentCount() ;

            /**
             * Get the amount of buffers that can be drawn at the same time.
             */
            exported static GLint GetMaxDrawBuffers() ;

            // Avoid copy/move operations.
            Framebuffer(const Framebuffer& copied) = delete ;
            Framebuffer(Framebuffer&& moved) = delete ;
            Framebuffer& operator=(const Framebuffer& copied) = delete ;
            Framebuffer& operator=(Framebuffer&& moved) = delete ;
    } ;
}

#endif
