/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actWorldSkybox.cpp-
 */

#include "Game/Actor/actWorldSkybox.hpp"
#include "Engine/System/GameSystem.hpp"
#include "Engine/System/RaylibGL.hpp"
#include "Engine/Constants/gfxConstants.hpp"
#include "Engine/Resource/resGraphicsResource.hpp"


void game::act::Skybox::onEnter()
{
    //TODO: Skybox needs to be rendered behind objects no matter what.
    generateModelRectPrism(vec3f(512.0f, 512.0f, 512.0f));

    mRenderFlags.boundingBoxInvisibleDebug = true;
    mRenderFlags.wireframeInvisibleDebug = true;

    const char* vertShader_s = TextFormat(mShaderPaths[VS_PATH_S], GFX_GLSL_VERSION),
              * fragShader_s = TextFormat(mShaderPaths[FS_PATH_S], GFX_GLSL_VERSION);

    const char* vertShader_c = TextFormat(mShaderPaths[VS_PATH_C], GFX_GLSL_VERSION),
              * fragShader_c = TextFormat(mShaderPaths[FS_PATH_C], GFX_GLSL_VERSION);

    getModelMaterial(0).shader = LoadShader(vertShader_s, fragShader_s);

    int v0[1] = { MATERIAL_MAP_CUBEMAP }, v1[1] = { isHdrEnabled }, v2[1] = { isHdrEnabled };

    SetShaderValue(
        getModelMaterial(0).shader, GetShaderLocation(
        getModelMaterial(0).shader, "envMap"), v0, SHADER_UNIFORM_INT);

    SetShaderValue(
        getModelMaterial(0).shader, GetShaderLocation(
        getModelMaterial(0).shader, "useGamma"), v1, SHADER_UNIFORM_INT);

    SetShaderValue(
        getModelMaterial(0).shader, GetShaderLocation(
        getModelMaterial(0).shader, "vFlipped"), v2, SHADER_UNIFORM_INT);

    mCubeMapShader = LoadShader(vertShader_c, fragShader_c);
    int eqRectMapValue[1] = { 0 };

    SetShaderValue(mCubeMapShader,
       GetShaderLocation(mCubeMapShader, "eqRectMap"), eqRectMapValue, SHADER_UNIFORM_SAMPLER2D);

    #ifdef PLATFORM_DESKTOP
    if (isHdrEnabled)
    {
        auto sky = LoadTexture(mTexturePath);

        getModelMaterial(0).maps[MATERIAL_MAP_CUBEMAP].texture =
            genTextureCubeMap(sky, 1024, PIXELFORMAT_UNCOMPRESSED_R32G32B32A32);

        UnloadTexture(sky);
        return;
    }
    #endif

    anim::res::ImageResFactory.load("SkyImage"_hs, mTexturePath);
    //auto sky = LoadImage(mTexturePath);

    getModelMaterial(0).maps[MATERIAL_MAP_CUBEMAP].texture =
        LoadTextureCubemap(
            *reinterpret_cast<Image*>(&anim::res::ImageResFactory.handle("SkyImage"_hs).get()),
            CUBEMAP_LAYOUT_AUTO_DETECT);

    anim::res::ImageResFactory.unload("SkyImage"_hs);
    //UnloadImage(sky);
}

void game::act::Skybox::onUpdate()
{

}

void game::act::Skybox::onPreRender()
{
    rlDisableBackfaceCulling();
    rlDisableDepthMask();

    mPosition = anim::GameSystem::instance().getCameraPosition();
}

void game::act::Skybox::onPostRender()
{
    rlEnableBackfaceCulling();
    rlEnableDepthMask();
}

void game::act::Skybox::onLeave()
{

}

TextureCubemap game::act::Skybox::genTextureCubeMap(Texture2D texture, s32 size, s32 format)
{
    TextureCubemap cb{};
    rlDisableBackfaceCulling();

    const u32 rb = rlLoadTextureDepth(size, size, true);
    const u32 fb = rlLoadFramebuffer(size, size);

    cb.id = rlLoadTextureCubemap(nullptr, size, format);

    rlFramebufferAttach(fb, rb, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);
    rlFramebufferAttach(fb, cb.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X, 0);

    if (rlFramebufferComplete(fb))
        TraceLog(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", fb);
    else
    {
        TraceLog(LOG_INFO, "FBO: [ID %i] Framebuffer object not complete", fb);
        return TextureCubemap {};
    }

    rlEnableShader(mCubeMapShader.id);
    Matrix fp = MatrixPerspective(90.f * DEG2RAD, 1.f, RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR);

    rlSetUniformMatrix(mCubeMapShader.locs[SHADER_LOC_MATRIX_PROJECTION], fp);
    rlViewport(0, 0, size, size);

    Matrix fv[6] =
    {
        MatrixLookAt({ 0.0f, 0.0f, 0.0f}, { 1.0f, 0.0f, 0.0f}, { 0.0f,-1.0f, 0.0f }),
        MatrixLookAt({ 0.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, { 0.0f,-1.0f, 0.0f }),
        MatrixLookAt({ 0.0f, 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f }),
        MatrixLookAt({ 0.0f, 0.0f, 0.0f}, { 0.0f,-1.0f, 0.0f}, { 0.0f, 0.0f,-1.0f }),
        MatrixLookAt({ 0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f, 1.0f}, { 0.0f,-1.0f, 0.0f }),
        MatrixLookAt({ 0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f,-1.0f}, { 0.0f,-1.0f, 0.0f })
    };

    for (s32 i = 0; i < 6; i++)
    {
        rlSetUniformMatrix(mCubeMapShader.locs[SHADER_LOC_MATRIX_VIEW], fv[i]);
        rlFramebufferAttach(fb, cb.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X + i, 0);

        rlEnableFramebuffer(fb);
        rlSetTexture(texture.id);

        rlClearScreenBuffers();
        DrawCubeV(Vector3Zero(), Vector3One(), WHITE);
        rlDrawRenderBatchActive();
    }

    rlDisableShader();
    rlDisableTexture();
    rlDisableFramebuffer();
    rlUnloadFramebuffer(fb);

    rlViewport(0, 0, rlGetFramebufferWidth(), rlGetFramebufferHeight());
    rlEnableBackfaceCulling();

    cb.width   = size;
    cb.height  = size;
    cb.mipmaps = 1;
    cb.format  = PIXELFORMAT_UNCOMPRESSED_R32G32B32;

    return cb;
}