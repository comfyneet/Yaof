#include "Yaof/Core/ResourceManager.hpp"
#include <sstream>
#include <vector>
#include "tinyxml2/tinyxml2.h"
#include "Yaof/Core/Resource.hpp"
#include "Yaof/Misc/Macros.hpp"
#include "Yaof/Misc/FileInputStream.hpp"
#include "Yaof/Image.hpp"

namespace yf
{
    bool ResourceManager::initialize(std::string const& xmlFilePath, uint32_t const currentScope)
    {
        if (m_initialized)
        {
            return false;
        }

        FileInputStream fileInputStream(xmlFilePath);
        const auto fileSize = fileInputStream.getSize();
        auto fileData = new char[fileSize + 1]();
        fileInputStream.seek(0);
        (void)fileInputStream.read(fileData, fileSize);

        tinyxml2::XMLDocument xmlDocument;
        const auto result = xmlDocument.Parse(fileData);

        if (result == tinyxml2::XML_NO_ERROR)
        {
            auto xmlResources = xmlDocument.FirstChildElement("Resources");

            if (xmlResources)
            {
                auto xmlResource = xmlResources->FirstChildElement("Resource");
                std::vector<std::string> resourceIds;

                while (xmlResource)
                {
                    const auto type = xmlResource->Attribute("type");
                    const auto id = xmlResource->Attribute("id");
                    const auto scope = xmlResource->Attribute("scope");
                    const auto filePath = xmlResource->Attribute("filePath");

                    if (type && id && scope && filePath)
                    {
                        if (std::find(resourceIds.begin(), resourceIds.end(), id) != resourceIds.end())
                        {
                            throw std::exception(
                                "ResourceManager cannot add new Resource due to resource id duplication.");
                        }
                        resourceIds.emplace_back(id);

                        std::unique_ptr<Resource, ResourceDeleter> resource;

                        if (strcmp(type, "Image") == 0)
                        {
                            resource.reset(new Image());
                            resource->m_type = ResourceType::Image;
                        }
                        else
                        {
                            /* TODO: other types */
                        }

                        if (resource)
                        {
                            resource->m_id = std::string(id);
                            std::stringstream(scope) >> resource->m_scope;
                            resource->m_filePath = std::string(filePath);

                            registerResource(std::move(resource));
                        }
                    }
                    else
                    {
                        throw std::exception(
                            "ResourceManager cannot find XML resource type, or id, or scope, or filePath.");
                    }

                    xmlResource = xmlResource->NextSiblingElement("Resource");
                }
            }
            else
            {
                throw std::exception("ResourceManager cannot find XML resources.");
            }
        }
        else
        {
            throw std::exception("ResourceManager cannot read XML file.");
        }

        YAOF_DELETE_ARRAY(fileData);

        loadResources(currentScope);

        m_initialized = !m_resources.empty();

        return m_initialized;
    }

    void ResourceManager::terminate()
    {
        if (!m_initialized)
        {
            return;
        }

        for (auto& resources : m_resources)
        {
            auto& list = resources.second;
            for (auto& resource : list)
            {
                if (resource->isLoaded())
                {
                    resource->unload();
                }

                resource.reset();
            }

            list.clear();
        }

        m_resources.clear();

        m_initialized = false;
    }

    void ResourceManager::setCurrentScope(uint32_t const currentScope)
    {
        if (m_currentScope != currentScope)
        {
            unloadResources(m_currentScope);
            m_currentScope = currentScope;
            loadResources(m_currentScope);
        }
    }

    uint32_t ResourceManager::getCurrentScope() const
    {
        return m_currentScope;
    }

    Resource const& ResourceManager::getResource(std::string const& resourceId)
    {
        for (auto& resources : m_resources)
        {
            for (auto& resource : resources.second)
            {
                if (resource->getId() == resourceId)
                {
                    return *resource;
                }
            }
        }

        throw std::exception("ResourceManager cannot find Resource with given resource id.");
    }

    ResourceManager::ResourceManager() :
        m_initialized(false),
        m_currentScope(0)
    {
    }

    ResourceManager::~ResourceManager()
    {
        terminate();
    }

    void ResourceManager::registerResource(std::unique_ptr<Resource, ResourceDeleter> resource)
    {
        const auto it = m_resources.find(resource->getScope());

        std::list<std::unique_ptr<Resource, ResourceDeleter>>* list;
        if (it == m_resources.end())
        {
            m_resources[resource->getScope()] = std::list<std::unique_ptr<Resource, ResourceDeleter>>();
            list = &m_resources[resource->getScope()];
        }
        else
        {
            list = &(*it).second;
        }

        list->push_back(std::move(resource));
    }

    void ResourceManager::unloadResources(uint32_t const scope)
    {
        for (auto& resources : m_resources)
        {
            if (resources.first == scope)
            {
                for (auto& resource : resources.second)
                {
                    if (resource->isLoaded())
                    {
                        resource->unload();
                    }
                }

                break;
            }
        }
    }

    void ResourceManager::loadResources(uint32_t const scope)
    {
        for (auto& resources : m_resources)
        {
            if (resources.first == scope)
            {
                for (auto& resource : resources.second)
                {
                    if (!resource->isLoaded())
                    {
                        resource->load();
                    }
                }

                break;
            }
        }
    }

    void ResourceManager::ResourceDeleter::operator()(Resource* resource) const
    {
        YAOF_DELETE(resource);
    }
}
