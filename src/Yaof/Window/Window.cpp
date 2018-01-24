#include "Yaof/Window/Window.hpp"
#include "GLFW/glfw3.h"
#include "Yaof/Misc/Macros.hpp"

namespace yf
{
    GLFWwindow* create(int32_t width, int32_t height, std::string const& title);

    Window::Window(int32_t const width, int32_t const height, std::string const& title)
    {
        m_glfwWindow.reset(create(width, height, title));
        if (!m_glfwWindow.get())
        {
            throw std::exception("Cannot create Window.");
        }
    }

    GLFWwindow const& Window::getGlfwWindow() const
    {
        return *m_glfwWindow;
    }

    GLFWwindow* create(int32_t const width, int32_t const height, std::string const& title)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, YAOF_CONTEXT_VERSION_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, YAOF_CONTEXT_VERSION_MINOR);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        const auto glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        return glfwWindow;
    }

    void Window::WindowDeleter::operator()(GLFWwindow* glfwWindow) const
    {
        glfwDestroyWindow(glfwWindow);
    }
}
