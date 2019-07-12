#include <scene/ogl/rendering/framebuffers/Framebuffer.hpp>
#include <utils/LogSystem.hpp>
#include <HOPEStrings.hpp>

using namespace Hope::GL ;

const bool Framebuffer::GenerateMipmaps = false ;

Framebuffer::Framebuffer() {
    glGenFramebuffers(1, &m_fboID) ;
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_fboID) ;
}

void Framebuffer::setDrawBuffers(const std::list<unsigned char> indices) {
    std::vector<unsigned int> attachments ;
    for (unsigned char index: indices) {
        attachments.push_back(GL_COLOR_ATTACHMENT0 + index) ;
    }

    bind(AccessMode::WriteOnly) ;
    glNamedFramebufferDrawBuffers(m_fboID, attachments.size(), attachments.data()) ;
    unbind(AccessMode::WriteOnly) ;
}

void Framebuffer::useNoColorBuffers() {
    bind() ;
    glDrawBuffer(GL_NONE) ;
    glReadBuffer(GL_NONE) ;
    unbind() ;
}

void Framebuffer::detachColor(const int attachmentIndex) {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fboID) ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0 + attachmentIndex,
        GL_TEXTURE_2D,
        0,
        MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer::detachDepth() {
    // Attach the texture to the framebuffer.
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D,
        0,
        MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer::detachStencil() {
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,
        0,
        MipmapLevel
    ) ;
    unbind() ;
}

void Framebuffer::detachDepthStencil() {
    bind() ;
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,
        0,
        MipmapLevel
    ) ;
    unbind() ;
}

GLint Framebuffer::GetColorAttachmentCount() {
    GLint maxColorAttachments = 0 ;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxColorAttachments) ;
    return maxColorAttachments ;
}

GLint Framebuffer::GetMaxDrawBuffers() {
    GLint maxDrawBuffers = 0 ;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawBuffers) ;
    return maxDrawBuffers ;
}

bool Framebuffer::isComplete() const {
    const GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER) ;
    const bool IsComplete = Status == GL_FRAMEBUFFER_COMPLETE ;

    if (!IsComplete) {
        std::string errorLog ;
        switch (Status) {
            case GL_FRAMEBUFFER_UNDEFINED:
                errorLog = Hope::Texts::FBO_Undefined ;
                break ;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                errorLog = Hope::Texts::FBO_IncompleteAttachment ;
                break ;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                errorLog = Hope::Texts::FBO_IncompleteMissingAttachment ;
                break ;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                errorLog = Hope::Texts::FBO_IncompleteDrawBuffer ;
                break ;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                errorLog = Hope::Texts::FBO_IncompleteReadBuffer ;
                break ;
            case GL_FRAMEBUFFER_UNSUPPORTED:
                errorLog = Hope::Texts::FBO_Unsupported ;
                break ;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                errorLog = Hope::Texts::FBO_IncompleteMultisample ;
                break ;
            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
                errorLog = Hope::Texts::FBO_IncompleteLayerTargets ;
                break ;
            default:
                errorLog = Hope::Texts::FBO_UnknownError ;
                break ;
        }

        // Write the error in the log.
        auto logWeakPtr = Doom::LogSystem::GetInstance() ;
        auto logSharedPtr = logWeakPtr.lock() ;
        if (logSharedPtr) {
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;
            logSharedPtr -> writeLine(level, errorLog) ;
        }
    }

    return IsComplete ;
}