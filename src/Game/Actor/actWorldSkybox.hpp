/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actWorldSkybox.hpp-
 */

#pragma once
#include "Engine/Actor/actBaseActor.hpp"
#include "Engine/System/Raylib.hpp"

namespace game::act
{

class Skybox : public anim::act::ActorModel
{
public:
    Skybox(const char* shaders[4], const char* texture, bool useHdr)
    :
    mShaderPaths{shaders[0], shaders[1], shaders[2], shaders[3]},
    mTexturePath(texture), isHdrEnabled(useHdr) {}

    enum ShaderPathValue
    {
        VS_PATH_S = 0, FS_PATH_S = 1,
        VS_PATH_C = 2, FS_PATH_C = 3
    };

    void onEnter() override;
    void onUpdate() override;
    void onPreRender() override;
    void onPostRender() override;
    void onLeave() override;

    TextureCubemap genTextureCubeMap(Texture2D texture, s32 size, s32 format);
private:
    Shader mCubeMapShader{};

    const char* mShaderPaths[4];
    const char* mTexturePath;
    const bool isHdrEnabled;
};

}