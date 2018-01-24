#ifndef YAOF_CORE_APPLICATION_HPP
#define YAOF_CORE_APPLICATION_HPP

#include <memory>
#include <string>
#include "Yaof/Core/Configuration.hpp"
#include "Yaof/Misc/Singleton.hpp"

namespace yf
{
    class Application;
    class Window;
    YAOF_EXTERN template class YAOF_DLL Singleton<Application>;

    class YAOF_DLL Application : public Singleton<Application>
    {
        friend class Singleton<Application>;
    public:
        ~Application();

        Window const& getWindow() const;

        bool initialize(int32_t width, int32_t height, std::string const& title = "");

        void terminate();

    private:
        Application();

        bool m_initialized;

        std::unique_ptr<Window> m_window;
    };
}

#endif
