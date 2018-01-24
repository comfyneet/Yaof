#ifndef YAOF_IMAGE_HPP
#define YAOF_IMAGE_HPP

#include <memory>
#include "Yaof/Core/Configuration.hpp"
#include "Yaof/Core/Resource.hpp"

struct FIBITMAP;

namespace yf
{
    class YAOF_DLL Image : public Resource
    {
        friend class ResourceManager;
    public:

        void load() override;

        void unload() override;

        uint32_t getHeight() const;

        uint32_t getWidth() const;

        uint32_t getBitsPerPixel() const;

        byte* getImage() const;

    private:
        struct ImageDeleter
        {
            void operator()(FIBITMAP*) const;
        };

        Image();

        ~Image();

        uint32_t m_height;

        uint32_t m_width;

        uint32_t m_bpp;

        std::unique_ptr<FIBITMAP, ImageDeleter> m_image;
    };
}

#endif
