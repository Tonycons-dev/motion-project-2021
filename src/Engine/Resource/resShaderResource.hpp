#pragma once

#include "Engine/Resource/resResourceBase.hpp"
#include "Engine/System/Raymath.hpp"
#include "Engine/System/Raylib.hpp"

namespace anim::res {

class ShaderResource
{
private:
    RESOURCE_IMPL(Shader)
public:
    ShaderResource(const char* vs, const char* fs);
    ~ShaderResource();

    void setUniformFloat(const char* name, f32 value);
    void setUniformInt(const char* name, s32 value);
    void setUniformVec2(const char* name, const vec2f& value);
    void setUniformVec3(const char* name, const vec3f& value);
    void setUniformVec4(const char* name, const vec4f& value);
    void setUniformRGB (const char* name, const vec3b& value);
    void setUniformRGBA(const char* name, const vec4b& value);
};

class ShaderResLoader : public entt::resource_loader<ShaderResLoader, ShaderResource>
{
public:
    std::shared_ptr<ShaderResource> load(const char* vs, const char* fs) const {
        return std::make_shared<ShaderResource>(vs, fs);
    }
};

class ShaderResFactory_ : public ResourceFactory<ShaderResource, ShaderResLoader>{};
extern ShaderResFactory_ ShaderResFactory;
}