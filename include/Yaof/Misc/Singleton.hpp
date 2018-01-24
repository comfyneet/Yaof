#ifndef YAOF_MISC_SINGLETON_HPP
#define YAOF_MISC_SINGLETON_HPP

#include "Yaof/Misc/NonCopyable.hpp"

namespace yf
{
    template <typename T>
    class YAOF_TEMPLATE_DLL Singleton : public NonCopyable
    {
    public:
        static T& getInstance();

        virtual ~Singleton() = default;

    protected:
        Singleton();
    };

#include "Yaof/Misc/Singleton.inl"
}

#endif
