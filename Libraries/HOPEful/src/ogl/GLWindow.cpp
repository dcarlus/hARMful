#include <HOPEStrings.hpp>
#include <ogl/GLWindow.hpp>
#include <ogl/GLOptions.hpp>
#include <utils/LogSystem.hpp>
#include <iostream>
#include <cstdlib>

namespace Hope {
    GLWindow::GLWindow(
        const int width,
        const int height,
        const std::string& title
    ) {
        createInternalWindow(width, height, title);
        useCurrentContext();
        initializeGLEW();
        setInputMode();
    }

    GLWindow::~GLWindow() {}

    void GLWindow::swapBuffers() {
        glfwSwapBuffers(m_window);
    }

    void GLWindow::createInternalWindow(
        const int width,
        const int height,
        const std::string& title
    ) {
        if (!glfwInit()) {
            auto logWeakPtr = Doom::LogSystem::GetInstance() ;
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;

            auto logSharedPtr = logWeakPtr.lock() ;
            if (logSharedPtr) {
                logSharedPtr -> writeLine(level, Texts::Init_Bad_GLFW) ;
            }

            exit(EXIT_FAILURE);
        }

        m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (m_window == nullptr) {
            auto logWeakPtr = Doom::LogSystem::GetInstance() ;
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;

            auto logSharedPtr = logWeakPtr.lock() ;
            if (logSharedPtr) {
                logSharedPtr -> writeLine(level, Texts::Init_GL_Window) ;
            }

            glfwTerminate();
            exit(EXIT_FAILURE);
        }
    }

    void GLWindow::useCurrentContext() {
        glfwMakeContextCurrent(m_window);
    }

    void GLWindow::initializeGLEW()    {
        // Required for the core profile set in the main window.
        glewExperimental = true;

        GLenum initEror = glewInit();

        if (initEror != GLEW_OK) {
            auto logWeakPtr = Doom::LogSystem::GetInstance() ;
            Doom::LogSystem::Gravity level = Doom::LogSystem::Gravity::Critical ;

            auto logSharedPtr = logWeakPtr.lock() ;
            if (logSharedPtr) {
                logSharedPtr -> writeLine(
                    level,
                    Texts::Init_Bad_GLEW,
                    glewGetErrorString(initEror)
                ) ;
            }

            exit(EXIT_FAILURE);
        }
    }

    void GLWindow::setInputMode() {
        glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
    }
}