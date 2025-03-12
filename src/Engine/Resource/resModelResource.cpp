#include "Engine/Resource/resModelResource.hpp"

anim::res::ModelResFactory_ anim::res::ModelResFactory;


anim::res::ModelResource::ModelResource(const char *filepath)
{
    ASSERT_RESOURCE_FILE("ModelResource", filepath)
    mResource = LoadModel(filepath);
}

anim::res::ModelResource::ModelResource(const RlModel &model)
{
    mResource = model;
    mResourceValid = true;

    if (mResource.meshes == nullptr)
        mResourceValid = false;
}

anim::res::ModelResource::~ModelResource()
{
    if (isResourceValid())
        UnloadModel(mResource);
}