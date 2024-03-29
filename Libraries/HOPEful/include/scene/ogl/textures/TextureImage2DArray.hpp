#ifndef __HOPE__GL_TEXTURE2D_ARRAY__
#define __HOPE__GL_TEXTURE2D_ARRAY__

#include <utils/Platform.hpp>

#include <scene/ogl/textures/Texture.hpp>
#include <vector>

namespace Hope::GL {
    /**
     * Buffer of stacked 2D textures.
     */
    class TextureImage2DArray final : public Texture {
        public:
            /**
             * Amount of coordinates for the TextureImage2DArray class.
             */
            static const int AmountCoordinates = 3 ;

        private:
            /**
             * Size of the texture.
             */
            Mind::Dimension3Di m_size ;

            /**
             * Pixel format of the input data.
             */
            PixelFormat m_pixelFormat ;

            /**
             * The way colors are encoded in memory the texture.
             */
            PixelDataType m_pixelDataType ;

            /**
             * Automatic mipmap generation if true.
             */
            bool m_mipmap ;

        public:
            /**
             * Create a new TextureImage2DArray instance.
             * @param   size            Size of the texture in pixels.
             * @param   internalFormat  Number of color components in the
             *                          texture.
             * @param   pixelFormat     Format of the pixel data.
             * @param   pixelDataType   Data type of the pixel data.
             * @param   pixelData       Raw data of the texture.
             *                          nullptr is a valid value, for example to
             *                          use the texture as a framebuffer texture
             *                          attachments.
             * @param   mipmap          Generate the mipmaps if true.
             */
            exported TextureImage2DArray(
                const Mind::Dimension3Di& size,
                const InternalFormat internalFormat,
                const PixelFormat pixelFormat,
                const PixelDataType pixelDataType,
                const unsigned char* pixelData = nullptr,
                const bool mipmap = true
            ) ;

            /**
             * Resize the texture.
             * @param   size        The new size to apply.
             * @param   pixelData   Pixel data that fit the new size.
             */
            exported void resize(
                const Mind::Dimension3Di& size,
                const unsigned char* pixelData = nullptr
            ) ;

            /**
             * Get the texture width.
             * @return  The texture width.
             */
            exported uint32_t width() const {
                return m_size.width() ;
            }

            /**
             * Get the texture height.
             * @return  The texture height.
             */
            exported uint32_t height() const {
                return m_size.height() ;
            }

            /**
             * Get the texture depth.
             * @return  The texture depth.
             */
            exported uint32_t depth() const {
                return m_size.depth() ;
            }

            /**
             * Get the pixel format of the texture.
             */
            exported PixelFormat pixelFormat() const {
                return m_pixelFormat ;
            }

            /**
             * Get the pixel data type of the texture.
             */
            exported PixelDataType pixelDataType() const {
                return m_pixelDataType ;
            }

            /**
             * Set the wrap mode for each dimension of the texture.
             */
            exported void setWrapModes(std::array<WrapMode, AmountCoordinates> modes) ;
    } ;
}

#endif
