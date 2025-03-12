#include "Engine/Resource/resShaderResource.hpp"

anim::res::ShaderResFactory_ anim::res::ShaderResFactory;

anim::res::ShaderResource::ShaderResource(const char* vs, const char* fs)
{
    ASSERT_RESOURCE_FILE("ShaderResource: Vertex Shader", vs)
    ASSERT_RESOURCE_FILE("ShaderResource: Fragment Shader", fs)
    mResource = LoadShader(vs, fs);
}

anim::res::ShaderResource::~ShaderResource()
{
    if (isResourceValid())
        UnloadShader(mResource);
}

#define CHECK_UNIFORM_TYPE(uniformType, uniformName)                                \
    if (!isResourceValid()) {                                                       \
        TraceLog(LOG_WARNING,                                                       \
        "[ShaderResource] Setting uniform for invalid resource.");                  \
        return;                                                                     \
    }                                                                               \
    int index = GetShaderLocation(mResource, uniformName);                          \
                                                                                    \
    if (index == -1) {                                                              \
        TraceLog(LOG_ERROR,                                                         \
        "[ShaderResource] Uniform %s is not found as a " uniformType, uniformName); \
        return;                                                                     \
    }

void anim::res::ShaderResource::setUniformFloat(const char* name, f32 value)
{
    CHECK_UNIFORM_TYPE("SHADER_UNIFORM_FLOAT", name)
    SetShaderValue(mResource, index, &value, SHADER_UNIFORM_FLOAT);
}

void anim::res::ShaderResource::setUniformInt(const char* name, s32 value)
{
    CHECK_UNIFORM_TYPE("SHADER_UNIFORM_INT", name)
    SetShaderValue(mResource, index, &value, SHADER_UNIFORM_INT);
}

void anim::res::ShaderResource::setUniformVec2(const char* name, const vec2f &value)
{
    CHECK_UNIFORM_TYPE("SHADER_UNIFORM_VEC2", name)
    SetShaderValue(mResource, index, &value, SHADER_UNIFORM_VEC2);
}

void anim::res::ShaderResource::setUniformVec3(const char* name, const vec3f &value)
{
    CHECK_UNIFORM_TYPE("SHADER_UNIFORM_VEC3", name)
    SetShaderValue(mResource, index, &value, SHADER_UNIFORM_VEC3);
}

void anim::res::ShaderResource::setUniformVec4(const char* name, const vec4f &value)
{
    CHECK_UNIFORM_TYPE("SHADER_UNIFORM_VEC4", name)
    SetShaderValue(mResource, index, &value, SHADER_UNIFORM_VEC4);
}

void anim::res::ShaderResource::setUniformRGB(const char* name, const vec3b &value)
{
    CHECK_UNIFORM_TYPE("SHADER_UNIFORM_VEC3", name)

    const vec3f data[1]{
    {f32(value.x) / 255.f, f32(value.y) / 255.f, f32(value.z) / 255.f}};

    SetShaderValue(mResource, index, data, SHADER_UNIFORM_VEC3);
}

void anim::res::ShaderResource::setUniformRGBA(const char* name, const vec4b &value)
{
    CHECK_UNIFORM_TYPE("SHADER_UNIFORM_VEC4", name)

    const vec4f data[1]{{f32(value.x) / 255.f, f32(value.y) / 255.f,
                         f32(value.z) / 255.f, f32(value.w) / 255.f}};

    SetShaderValue(mResource, index, data, SHADER_UNIFORM_VEC4);
}