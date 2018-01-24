#ifndef YAOF_GRAPHICS_SHADER_HPP
#define YAOF_GRAPHICS_SHADER_HPP

#include <cstdint>
#include "Yaof/Core/Configuration.hpp"
#include "Yaof/Misc/NonCopyable.hpp"

namespace yf
{
    class InputStream;

    class YAOF_DLL Shader : public NonCopyable
    {
    public:
        Shader();

        Shader(InputStream const& vertexStream, InputStream const& fragmentStream);

        Shader(
            byte const* vertexBuffer,
            uint32_t vertexSize,
            byte const* fragmentBuffer,
            uint32_t fragmentSize);

        ~Shader();

        uint32_t getGlProgramId() const;

        uint32_t getGlVertexId() const;

        uint32_t getGlFragmentId() const;

        void use() const;

    private:
        uint32_t m_glProgramId;

        uint32_t m_glVertexId;

        uint32_t m_glFragmentId;
    };
}

#endif
