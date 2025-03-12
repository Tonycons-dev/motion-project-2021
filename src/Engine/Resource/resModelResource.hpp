#pragma once

#include "Engine/Resource/resResourceBase.hpp"
#include "Engine/System/Raymath.hpp"
#include "Engine/System/Raylib.hpp"

namespace anim::res {

class ModelResource
{
private:
    RESOURCE_IMPL(Model)
public:
    explicit ModelResource(const char* filepath);
    explicit ModelResource(const Model& model);

    ~ModelResource();
    vec3f mDimensions;
};

class ModelResLoader : public entt::resource_loader<ModelResLoader, ModelResource>
{
public:
    std::shared_ptr<ModelResource> load(const char* filepath) const {
        return std::make_shared<ModelResource>(filepath);
    }

    std::shared_ptr<ModelResource> load(const RlModel& model) const {
        return std::make_shared<ModelResource>(model);
    }
};

class ModelResFactory_ : public ResourceFactory<ModelResource, ModelResLoader>{};
extern ModelResFactory_ ModelResFactory;
}