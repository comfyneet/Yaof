#ifndef YAOF_MISC_INPUTSTREAM_HPP
#define YAOF_MISC_INPUTSTREAM_HPP

#include "Yaof/Core/Configuration.hpp"
#include "Yaof/Misc/NonCopyable.hpp"

namespace yf
{
    class YAOF_DLL InputStream : public NonCopyable
    {
    public:
        InputStream() = default;

        virtual ~InputStream() = default;

        virtual bool read(void* data, long size) const = 0;

        virtual void seek(long position) const = 0;

        virtual long tell() const = 0;

        virtual long getSize() const = 0;
    };
}

#endif
