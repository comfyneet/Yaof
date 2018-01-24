#include "Yaof/Core/Resource.hpp"

namespace yf
{
    std::string const& Resource::getId() const
    {
        return m_id;
    }

    uint32_t Resource::getScope() const
    {
        return m_scope;
    }

    ResourceType Resource::getType() const
    {
        return m_type;
    }

    bool Resource::isLoaded() const
    {
        return m_loaded;
    }

    std::string const& Resource::getFilePath() const
    {
        return m_filePath;
    }

    Resource::Resource() :
        m_type(ResourceType::Null),
        m_scope(YAOF_DEFAULT_RESOURCE_GLOBAL_SCOPE),
        m_loaded(false)
    {
    }

    void Resource::setLoaded(bool const loaded)
    {
        m_loaded = loaded;
    }
}
