#ifndef YAOF_CORE_RESOURCEMANAGER_HPP
#define YAOF_CORE_RESOURCEMANAGER_HPP

#include <list>
#include <map>
#include <memory>
#include "Yaof/Core/Configuration.hpp"
#include "Yaof/Misc/Singleton.hpp"

namespace yf
{
    class Resource;
    class ResourceManager;
    YAOF_EXTERN template class YAOF_DLL Singleton<ResourceManager>;

    class YAOF_DLL ResourceManager : public Singleton<ResourceManager>
    {
        friend class Singleton<ResourceManager>;
    public:
        bool initialize(std::string const& xmlFilePath, uint32_t currentScope = 0);

        void terminate();

        void setCurrentScope(uint32_t currentScope);

        uint32_t getCurrentScope() const;

        Resource const& getResource(std::string const& resourceId);

    private:
        struct ResourceDeleter
        {
            void operator()(Resource*) const;
        };

        ResourceManager();

        ~ResourceManager();

        void registerResource(std::unique_ptr<Resource, ResourceDeleter> resource);

        void unloadResources(uint32_t scope);

        void loadResources(uint32_t scope);

        bool m_initialized;

        uint32_t m_currentScope;

        std::map<uint32_t, std::list<std::unique_ptr<Resource, ResourceDeleter>>> m_resources;
    };
}

#endif
