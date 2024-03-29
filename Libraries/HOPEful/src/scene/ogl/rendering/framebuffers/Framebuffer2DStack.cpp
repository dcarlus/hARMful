#include <scene/ogl/rendering/framebuffers/Framebuffer2DStack.hpp>
#include <scene/ogl/textures/formats/WrapModes.hpp>
#include <HOPEStrings.hpp>

using namespace Hope::GL ;

Framebuffer2DStack::Framebuffer2DStack()
    : Framebuffer() {
    m_colorAttachments.resize(GetColorAttachmentCount()) ;
}

Framebuffer2DStack::Framebuffer2DStack(const Mind::Dimension3Di& size)
    : Framebuffer(),
      m_size(size) {
    m_colorAttachments.resize(GetColorAttachmentCount()) ;
}

void Framebuffer2DStack::resize(const Mind::Dimension2Di& newSize) {
    Mind::Dimension3Di newSize3D(
        newSize.width(),
        newSize.height(),
        m_size.depth()
    ) ;

    resize(newSize3D) ;
}

void Framebuffer2DStack::resize(const Mind::Dimension3Di& newSize) {
    if (m_size == newSize) {
        return ;
    }

    m_size = newSize ;

    const size_t MaxColorAttachments = m_colorAttachments.size() ;
    for (size_t colorIndex = 0; colorIndex < MaxColorAttachments; ++colorIndex) {
        if (m_colorAttachments[colorIndex]) {
            m_colorAttachments[colorIndex] -> resize(m_size) ;
        }
    }

    if (m_depthAttachment) {
        m_depthAttachment -> resize(m_size) ;
    }

    if (m_stencilAttachment) {
        m_stencilAttachment -> resize(m_size) ;
    }

    if (m_depthStencilAttachment) {
        m_depthStencilAttachment -> resize(m_size) ;
    }
}

void Framebuffer2DStack::attachColor(
    const unsigned char attachmentIndex,
    const InternalFormat internalFormat,
    const PixelFormat pixelDataFormat,
    const PixelDataType pixelDataType
) {
    if (!m_colorAttachments[attachmentIndex]) {
        // Generate the texture.
        m_colorAttachments[attachmentIndex] = std::make_unique<TextureImage2DArray>(
            m_size,
            internalFormat,
            pixelDataFormat,
            pixelDataType,
            nullptr,
            Framebuffer::GenerateMipmaps
        ) ;

        // Set the filtering modes.
        m_colorAttachments[attachmentIndex] -> bind() ;
        m_colorAttachments[attachmentIndex] -> setFiltering(FilterMode::Linear, FilterMode::Linear) ;
        m_colorAttachments[attachmentIndex] -> unbind() ;
    }

    // Attach the texture to the framebuffer.
    attachColor(attachmentIndex, m_colorAttachments[attachmentIndex].get()) ;
}

void Framebuffer2DStack::attachColor(
    const unsigned char attachmentIndex,
    const Texture* texture
) {
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0 + attachmentIndex,
        GL_TEXTURE_2D,
        texture -> id(),
        Framebuffer::MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer2DStack::attachDepth() {
    if (!m_depthAttachment) {
        // Generate the texture.
        m_depthAttachment = std::make_unique<TextureImage2DArray>(
            m_size,
            InternalFormat::DepthComponent,
            PixelFormat::DepthComponent,
            PixelDataType::UnsignedByte,
            nullptr,
            Framebuffer::GenerateMipmaps
        ) ;
    }

    // Set the filtering modes.
    m_depthAttachment -> bind() ;
    m_depthAttachment -> setFiltering(FilterMode::Linear, FilterMode::Linear) ;
    m_depthAttachment -> setWrapModes({ ClampToBorder, ClampToBorder, ClampToBorder }) ;
    m_depthAttachment -> setBorderColor(Hope::Color(1.f, 1.f, 1.f, 1.f)) ;
    m_depthAttachment -> setCompareRefToTexture(true) ;
    m_depthAttachment -> setComparisonOperator(ComparisonOperator::LessOrEqual) ;
    m_depthAttachment -> unbind() ;

    // Attach the texture to the framebuffer.
    attachDepth(m_depthAttachment.get()) ;
}

void Framebuffer2DStack::attachDepth(const Texture* texture) {
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D,
        texture -> id(),
        Framebuffer::MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer2DStack::attachStencil() {
    if (!m_stencilAttachment) {
        // Generate the texture.
        m_stencilAttachment = std::make_unique<TextureImage2DArray>(
            m_size,
            InternalFormat::StencilIndex,
            PixelFormat::StencilIndex,
            PixelDataType::UnsignedByte,
            nullptr,
            Framebuffer::GenerateMipmaps
        ) ;
    }

    // Set the filtering modes.
    m_stencilAttachment -> bind() ;
    m_stencilAttachment -> setFiltering(FilterMode::Linear, FilterMode::Linear) ;
    m_stencilAttachment -> unbind() ;

    // Attach the texture to the framebuffer.
    attachStencil(m_stencilAttachment.get()) ;
}

void Framebuffer2DStack::attachStencil(const Texture* texture) {
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,
        texture -> id(),
        Framebuffer::MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer2DStack::attachDepthStencil() {
    if (!m_depthStencilAttachment) {
        // Generate the texture.
        m_depthStencilAttachment = std::make_unique<TextureImage2DArray>(
            m_size,
            InternalFormat::Depth24Stencil8,
            PixelFormat::DepthStencil,
            PixelDataType::UnsignedInt248,
            nullptr,
            Framebuffer::GenerateMipmaps
        ) ;
    }

    // Set the filtering modes.
    m_depthStencilAttachment -> bind() ;
    m_depthStencilAttachment -> setFiltering(FilterMode::Linear, FilterMode::Linear) ;
    m_depthStencilAttachment -> unbind() ;

    // Attach the texture to the framebuffer.
    attachDepthStencil(m_depthStencilAttachment.get()) ;
}

void Framebuffer2DStack::attachDepthStencil(const Texture* texture) {
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,
        texture -> id(),
        Framebuffer::MipmapLevel
    ) ;
    unbind() ;
}
