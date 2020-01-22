#include <scene/ogl/textures/TextureImage2D.hpp>
#include <scene/ogl/textures/TextureLoader.hpp>
#include <scene/ogl/textures/formats/FilterModes.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope ;
using namespace Hope::GL ;

TextureImage2D::TextureImage2D(
    const std::string& path,
    const bool mipmap
) : Texture(GL_TEXTURE_2D) {
    static const bool FlipVerticalAxis = true ;

    glBindTexture(GL_TEXTURE_2D, id()) ;
    TextureLoader::LoadFromFile(GL_TEXTURE_2D, path, FlipVerticalAxis) ;
    setFiltering(FilterMode::Linear_MipLinear, FilterMode::Linear_MipLinear) ;

    if (mipmap) {
        glGenerateMipmap(GL_TEXTURE_2D) ;
    }

    glBindTexture(GL_TEXTURE_2D, 0) ;
}

TextureImage2D::TextureImage2D(
    const Mind::Dimension2Di& size,
    const InternalFormat internalFormat,
    const PixelFormat pixelFormat,
    const PixelDataType pixelDataType,
    const float* pixelData,
    const bool mipmap
) : Texture(
        GL_TEXTURE_2D,
        internalFormat
    ),
    m_size(size),
    m_pixelFormat(pixelFormat),
    m_pixelDataType(pixelDataType),
    m_mipmap(mipmap) {
    resize(size, pixelData) ;
}

void TextureImage2D::resize(
    const Mind::Dimension2Di& size,
    const float* pixelData
) {
    m_size = size ;

    glBindTexture(GL_TEXTURE_2D, id()) ;

    const GLint TextureLoD = 0 ;
    const GLint Border = 0 ;
    glTexImage2D(
        GL_TEXTURE_2D,
        TextureLoD,
        static_cast<GLint>(internalFormat()),
        m_size.width(),
        m_size.height(),
        Border,
        static_cast<GLenum>(m_pixelFormat),
        static_cast<GLenum>(m_pixelDataType),
        pixelData
    ) ;

    if (m_mipmap) {
        glGenerateMipmap(GL_TEXTURE_2D) ;
    }

    glBindTexture(GL_TEXTURE_2D, 0) ;
}

void TextureImage2D::setWrapModes(std::array<WrapMode, AmountCoordinates> modes) {
    glTexParameteri(target(), GL_TEXTURE_WRAP_S, modes[0]) ;
    glTexParameteri(target(), GL_TEXTURE_WRAP_T, modes[1]) ;
}
