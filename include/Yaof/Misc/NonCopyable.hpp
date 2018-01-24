#ifndef YAOF_MISC_NONCOPYABLE_HPP
#define YAOF_MISC_NONCOPYABLE_HPP

#include "Yaof/Core/Configuration.hpp"

namespace yf
{
    class YAOF_DLL NonCopyable
    {
    public:
        NonCopyable() = default;

        virtual ~NonCopyable() = default;

        NonCopyable(NonCopyable const&) = delete;

        NonCopyable& operator =(NonCopyable const&) = delete;

        NonCopyable(NonCopyable&&) = delete;

        NonCopyable& operator=(NonCopyable&&) = delete;
    };
}

#endif
