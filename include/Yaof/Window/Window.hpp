#ifndef YAOF_WINDOW_WINDOW_HPP
#define YAOF_WINDOW_WINDOW_HPP

#include <memory>
#include <string>
#include "Yaof/Core/Configuration.hpp"
#include "Yaof/Misc/NonCopyable.hpp"

struct GLFWwindow;

namespace yf
{
    class YAOF_DLL Window : public NonCopyable
    {
    public:
        Window() = delete;

        Window(int32_t width, int32_t height, std::string const& title = "");

        GLFWwindow const& getGlfwWindow() const;

    private:
        struct WindowDeleter
        {
            void operator()(GLFWwindow*) const;
        };

        std::unique_ptr<GLFWwindow, WindowDeleter> m_glfwWindow;
    };
}

#endif
