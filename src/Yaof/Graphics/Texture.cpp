#include "Yaof/Graphics/Texture.hpp"
#include "GL/glew.h"
#include "Yaof/Image.hpp"

namespace yf
{
    Texture::Texture(Image const& image) :
        m_glTextureId(0)
    {
        glGenTextures(1, &m_glTextureId);
        glBindTexture(GL_TEXTURE_2D, m_glTextureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (image.getBitsPerPixel() == 24)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.getWidth(), image.getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE,
                         image.getImage());
        }
        else if (image.getBitsPerPixel() == 32)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE,
                         image.getImage());
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, 0);
            glDeleteTextures(1, &m_glTextureId);
            m_glTextureId = 0;

            throw std::exception("Texture cannot use Image other than 24 or 32 Bits Per Pixel.");
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_glTextureId);
    }

    uint32_t Texture::getGlTextureId() const
    {
        return m_glTextureId;
    }

    Texture::Texture() :
        m_glTextureId(0)
    {
    }
}
