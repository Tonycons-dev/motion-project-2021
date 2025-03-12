#pragma once

#include <entt/resource/cache.hpp>
#include <entt/core/hashed_string.hpp>
#include "Core/Types/BasicTypes.hpp"

using namespace entt::literals;
namespace anim::res {

template<typename Resource, typename Loader>
struct ResourceFactory
{
    template<typename... Args>
    inline entt::resource_handle<Resource> load(const ENTT_ID_TYPE id, Args&&... args) {
        return mCache.template load<Loader>(id, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline entt::resource_handle<Resource> reload(const ENTT_ID_TYPE id, Args&&... args) {
        return mCache.template reload<Loader>(id, std::forward<Args>(args)...);
    }

    template<typename... Args>
    [[nodiscard]] inline entt::resource_handle<Resource> temp(Args&&... args) const {
        return mCache.template temp<Loader>(std::forward<Args>(args)...);
    }

    [[nodiscard]] inline entt::resource_handle<Resource> handle(const ENTT_ID_TYPE id) const {
        return mCache.handle(id);
    }

    [[nodiscard]] inline bool contains(const ENTT_ID_TYPE id) const {
        return mCache.contains(id);
    }

    inline void unload(const ENTT_ID_TYPE id) { mCache.discard(id); }
private:
    entt::resource_cache<Resource> mCache;
};
}