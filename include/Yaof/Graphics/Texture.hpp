#ifndef YAOF_GRAPHICS_TEXTURE_HPP
#define YAOF_GRAPHICS_TEXTURE_HPP

#include <cstdint>
#include "Yaof/Core/Configuration.hpp"
#include "Yaof/Misc/NonCopyable.hpp"

namespace yf
{
    class Image;

    class YAOF_DLL Texture : public NonCopyable
    {
    public:
        explicit Texture(Image const& image);

        ~Texture();

        uint32_t getGlTextureId() const;

    private:
        Texture();

        uint32_t m_glTextureId;
    };
}

#endif
