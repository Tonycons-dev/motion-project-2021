#pragma once

#include "Engine/Resource/resResourceFactory.hpp"
#include "Engine/Resource/resFilesystem.hpp"
#include <entt/resource/loader.hpp>

namespace anim::res
{

template<typename Resource>
class ResourceLoader : public entt::resource_loader<ResourceLoader<Resource>, Resource>
{
public:
    std::shared_ptr<Resource> load(const char* value) const {
        return std::shared_ptr<Resource>(new Resource(value));
    }
};

#define RESOURCE_IMPL(Resource)                                          \
private:                                                                 \
    Resource mResource{};                                                \
    bool mResourceValid = true;                                          \
public:                                                                  \
    [[nodiscard]] inline const Resource& const_resource() const noexcept \
    { return mResource; }                                                \
                                                                         \
    [[nodiscard]] inline Resource & resource() noexcept                  \
    { return mResource; }                                                \
                                                                         \
    [[nodiscard]] bool isResourceValid() const noexcept                  \
    { return mResourceValid; }

#define ASSERT_RESOURCE_FILE(Resource, file_path)\
    if (!Filesystem::pathExists(file_path))\
    {\
        std::cerr << "[Anim] Failed to load " << Resource << " " << file_path << "\n"; \
        mResourceValid = false;\
        return;\
    }
}