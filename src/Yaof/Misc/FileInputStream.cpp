#ifdef _MSC_VER
#  define _CRT_NONSTDC_NO_WARNINGS
#  define _CRT_SECURE_NO_WARNINGS
#endif

#include "Yaof/Misc/FileInputStream.hpp"
#include <cstdio>
#include <sys/stat.h>

namespace yf
{
    FileInputStream::FileInputStream(std::string const& filePath)
    {
        m_file.reset(std::fopen(filePath.c_str(), "rb"));

        if (!m_file.get())
        {
            throw std::exception("FileInputStream cannot open file.");
        }
    }

    FileInputStream::~FileInputStream()
    {
        m_file.reset();
    }

    bool FileInputStream::open(std::string const& filePath)
    {
        m_file.reset(std::fopen(filePath.c_str(), "rb"));

        return m_file != nullptr;
    }

    bool FileInputStream::read(void* data, long const size) const
    {
        return std::fread(data, 1, size, m_file.get()) > 0;
    }

    void FileInputStream::seek(long const position) const
    {
        std::fseek(m_file.get(), position, SEEK_SET);
    }

    long FileInputStream::tell() const
    {
        return std::ftell(m_file.get());
    }

    long FileInputStream::getSize() const
    {
        const auto fileDescriptor = fileno(m_file.get());
        struct stat stat{};
        fstat(fileDescriptor, &stat);

        return stat.st_size;
    }

    void FileInputStream::FileDeleter::operator()(std::FILE* file) const
    {
        std::fclose(file);
    }
}
