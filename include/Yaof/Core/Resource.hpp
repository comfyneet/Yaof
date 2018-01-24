#ifndef YAOF_CORE_RESOURCE_HPP
#define YAOF_CORE_RESOURCE_HPP

#include <string>
#include "Yaof/Core/Configuration.hpp"
#include "Yaof/Misc/NonCopyable.hpp"

#define YAOF_DEFAULT_RESOURCE_GLOBAL_SCOPE 0

namespace yf
{
    enum class ResourceType
    {
        Null,
        Image,
        //Movie,
        //Audio,
        //Text
    };

    class YAOF_DLL Resource : public NonCopyable
    {
        friend class ResourceManager;
    public:
        virtual void load() = 0;

        virtual void unload() = 0;

        std::string const& getId() const;

        ResourceType getType() const;

        uint32_t getScope() const;

        bool isLoaded() const;

        std::string const& getFilePath() const;

    protected:
        Resource();

        virtual ~Resource() = default;

        void setLoaded(bool loaded);

    private:
        std::string m_id;

        ResourceType m_type;

        uint32_t m_scope;

        bool m_loaded;

        std::string m_filePath;
    };
}

#endif
