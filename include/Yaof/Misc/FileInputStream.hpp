#ifndef YAOF_MISC_FILEINPUTSTREAM_HPP
#define YAOF_MISC_FILEINPUTSTREAM_HPP

#include <cstdio>
#include <memory>
#include <string>
#include "Yaof/Core/Configuration.hpp"
#include "Yaof/Misc/InputStream.hpp"

namespace yf
{
    class YAOF_DLL FileInputStream : public InputStream
    {
    public:
        FileInputStream() = default;

        explicit FileInputStream(std::string const& filePath);

        ~FileInputStream();

        bool open(std::string const& filePath);

        bool read(void* data, long size) const override;

        void seek(long position) const override;

        long tell() const override;

        long getSize() const override;

    private:
        struct FileDeleter
        {
            void operator()(std::FILE*) const;
        };

        std::unique_ptr<std::FILE, FileDeleter> m_file;
    };
}

#endif
