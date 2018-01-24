#include "Yaof/Core/Application.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "FreeImage/FreeImage.h"
#include "Yaof/Core/ResourceManager.hpp"
#include "Yaof/Misc/Macros.hpp"
#include "Yaof/Window/Window.hpp"

namespace yf
{
    Application::~Application()
    {
        terminate();
    }

    Window const& Application::getWindow() const
    {
        if (!m_initialized)
        {
            throw std::exception("Cannot get Window before initializing Application.");
        }

        return *m_window;
    }

    bool Application::initialize(int32_t const width, int32_t const height, std::string const& title)
    {
        if (m_initialized)
        {
            return false;
        }

        if (glfwInit() != GL_TRUE)
        {
            return false;
        }

        try
        {
            m_window.reset(new Window(width, height, title));
        }
        catch (std::exception const&)
        {
            terminate();
            return false;
        }

        glfwMakeContextCurrent(const_cast<GLFWwindow *>(&m_window->getGlfwWindow()));

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            terminate();
            return false;
        }

        glViewport(0, 0, width, height);

        FreeImage_Initialise();

        YAOF_FPSLIMITER.setEnable(true);
        YAOF_FPSLIMITER.setFramesPersecond(120);

        m_initialized = true;

        return m_initialized;
    }

    void Application::terminate()
    {
        if (!m_initialized)
        {
            return;
        }

        FreeImage_DeInitialise();

        YAOF_FPSLIMITER.setEnable(false);
        YAOF_RESOURCEMANAGER.terminate();

        glfwTerminate();

        m_initialized = false;
    }

    Application::Application() :
        m_initialized(false)
    {
    }
}
