#include "Yaof/Image.hpp"
#include <fstream>
#include "FreeImage/FreeImage.h"

namespace yf
{
    void Image::load()
    {
        std::ifstream file(getFilePath().c_str());
        if (!file.good())
        {
            throw std::exception("Cannot open image file.");
        }

        const auto format = FreeImage_GetFileType(getFilePath().c_str(), 0);
        if (format == FIF_UNKNOWN)
        {
            throw std::exception("Cannot determine image format.");
        }
        if (!FreeImage_FIFSupportsReading(format))
        {
            throw std::exception("Cannot read image format.");
        }

        const auto bitmap = FreeImage_Load(format, getFilePath().c_str());
        if (!bitmap)
        {
            throw std::exception("Cannot load Image.");
        }

        m_width = FreeImage_GetWidth(bitmap);
        m_height = FreeImage_GetHeight(bitmap);
        m_bpp = FreeImage_GetBPP(bitmap);

        if (m_bpp == 24)
        {
            m_image.reset(bitmap);
        }
        else if (m_bpp == 32)
        {
            m_image.reset(bitmap);
        }
        else
        {
            m_bpp = 32;
            m_image.reset(FreeImage_ConvertTo32Bits(bitmap));
            FreeImage_Unload(bitmap);
        }

        setLoaded(true);
    }

    void Image::unload()
    {
        m_image.reset();

        setLoaded(false);
    }

    uint32_t Image::getHeight() const
    {
        if (!isLoaded())
        {
            throw std::exception("Cannot get Height before loading Image.");
        }

        return m_height;
    }

    uint32_t Image::getWidth() const
    {
        if (!isLoaded())
        {
            throw std::exception("Cannot get Width before loading Image.");
        }

        return m_width;
    }

    uint32_t Image::getBitsPerPixel() const
    {
        if (!isLoaded())
        {
            throw std::exception("Cannot get Bits Per Pixel before loading Image.");
        }

        return m_bpp;
    }

    byte* Image::getImage() const
    {
        return FreeImage_GetBits(m_image.get());
    }

    Image::Image() :
        m_height(0),
        m_width(0),
        m_bpp(0)
    {
    }

    Image::~Image()
    {
        m_image.reset();
    }

    void Image::ImageDeleter::operator()(FIBITMAP* image) const
    {
        FreeImage_Unload(image);
    }
}
