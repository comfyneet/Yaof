#include "Yaof/Graphics/Shader.hpp"
#include <exception>
#include "GL/glew.h"
#include "Yaof/Core/ResourceManager.hpp"
#include "Yaof/Misc/Macros.hpp"
#include "Yaof/Misc/InputStream.hpp"

namespace yf
{
    void create(
        byte const* vertexSource,
        byte const* fragmentSource,
        uint32_t& glProgramId,
        uint32_t& glVertexId, uint32_t& glFragmentId);

    Shader::Shader() :
        m_glProgramId(0),
        m_glVertexId(0),
        m_glFragmentId(0)
    {
    }

    Shader::Shader(InputStream const& vertexStream, InputStream const& fragmentStream) :
        m_glProgramId(0),
        m_glVertexId(0),
        m_glFragmentId(0)
    {
        const auto vertexSize = vertexStream.getSize();
        auto vertexSource = new byte[vertexSize + 1]();
        vertexStream.seek(0);
        (void)vertexStream.read(vertexSource, vertexSize);

        const auto fragmentSize = fragmentStream.getSize();
        auto fragmentSource = new byte[fragmentSize + 1]();
        fragmentStream.seek(0);
        (void)fragmentStream.read(fragmentSource, fragmentSize);

        std::exception_ptr e;
        try
        {
            create(vertexSource, fragmentSource, m_glProgramId, m_glVertexId, m_glFragmentId);
        }
        catch (const std::exception&)
        {
            e = std::current_exception();
        }

        YAOF_DELETE_ARRAY(vertexSource);
        YAOF_DELETE_ARRAY(fragmentSource);

        if (e)
        {
            std::rethrow_exception(e);
        }
    }

    Shader::Shader(
        byte const* vertexBuffer,
        const uint32_t vertexSize,
        byte const* fragmentBuffer,
        const uint32_t fragmentSize) :
        m_glProgramId(0),
        m_glVertexId(0),
        m_glFragmentId(0)
    {
        byte* vertexSource = new byte[vertexSize + 1]();
        byte* fragmentSource = new byte[fragmentSize + 1]();
        std::memcpy(vertexSource, vertexBuffer, vertexSize);
        std::memcpy(fragmentSource, fragmentBuffer, fragmentSize);

        std::exception_ptr e;
        try
        {
            create(vertexSource, fragmentSource, m_glProgramId, m_glVertexId, m_glFragmentId);
        }
        catch (const std::exception&)
        {
            e = std::current_exception();
        }

        YAOF_DELETE_ARRAY(vertexSource);
        YAOF_DELETE_ARRAY(fragmentSource);

        if (e)
        {
            std::rethrow_exception(e);
        }
    }

    Shader::~Shader()
    {
        glDeleteShader(m_glVertexId);
        glDeleteShader(m_glFragmentId);
        glDeleteProgram(m_glProgramId);
    }

    uint32_t Shader::getGlProgramId() const
    {
        return m_glProgramId;
    }

    uint32_t Shader::getGlVertexId() const
    {
        return m_glVertexId;
    }

    uint32_t Shader::getGlFragmentId() const
    {
        return m_glFragmentId;
    }

    void Shader::use() const
    {
        glUseProgram(m_glProgramId);
    }

    void create(
        byte const* vertexSource,
        byte const* fragmentSource,
        uint32_t& glProgramId,
        uint32_t& glVertexId,
        uint32_t& glFragmentId)
    {
        auto success = 0;
        auto vertex = reinterpret_cast<char const*>(vertexSource);
        auto fragment = reinterpret_cast<char const*>(fragmentSource);

        const auto vertexId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexId, 1, &vertex, nullptr);
        glCompileShader(vertexId);
        glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glDeleteShader(vertexId);
            throw std::exception("Cannot create Vertex shader.");
        }

        const auto fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentId, 1, &fragment, nullptr);
        glCompileShader(fragmentId);
        glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glDeleteShader(vertexId);
            glDeleteShader(fragmentId);
            throw std::exception("Cannot create Fragment shader.");
        }

        const auto programId = glCreateProgram();
        glAttachShader(programId, vertexId);
        glAttachShader(programId, fragmentId);
        glLinkProgram(programId);
        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if (!success)
        {
            glDeleteShader(vertexId);
            glDeleteShader(fragmentId);
            glDeleteProgram(programId);
            throw std::exception("Cannot create Program.");
        }

        glProgramId = programId;
        glVertexId = vertexId;
        glFragmentId = fragmentId;
    }
}
