#include "Engine/Graphics/gfxPostProcessor.hpp"
#include "Engine/System/RaylibGL.hpp"
#include "Engine/System/GameSystem.hpp"
#include "Engine/Resource/resShaderResource.hpp"

void anim::gfx::PostProcessor::initialize(const EffectFlags& effectFlags)
{
    if (!anim::GameSystem::instance().mFlags.graphicsCtxActive) {
        TraceLog(LOG_ERROR,
        "[gfxPostProcessor] Initializing without a valid graphical context.");
        return;
    }

    auto handle = res::ShaderResFactory.load("PostProcessor_Shader"_hs,
        "res/shaders/postprocessor/vs_330_postprocess.shader",
        "res/shaders/postprocessor/fs_330_postprocess.shader");

    if (!handle->isResourceValid()) {
        TraceLog(LOG_ERROR, "[gfxPostProcessor] Shaders could not be loaded.");
        return;
    }
    else TraceLog(LOG_INFO, "[gfxPostProcessor] Shaders loaded successfully.");

    mFlags = effectFlags;
    enableEffect(mFlags.antialiasingEnabled, EffectType::ANTIALIASING);
    enableEffect(mFlags.heatDistortEnabled, EffectType::HEAT_DISTORT);
    enableEffect(mFlags.distanceFogEnabled, EffectType::DISTANCE_FOG);
}

void anim::gfx::PostProcessor::enableEffect(bool enable, EffectType effectType)
{
    if (!anim::GameSystem::instance().mFlags.graphicsCtxActive) {
        TraceLog(LOG_ERROR,
        "[gfxPostProcessor] Toggling effects without a valid graphical context.");
        return;
    }
    if (!res::ShaderResFactory.handle("PostProcessor_Shader"_hs)->isResourceValid()
    && effectType != EffectType::ANTIALIASING) {
        TraceLog(LOG_ERROR,
        "[gfxPostProcessor] Toggling effects without shaders loaded.");
        return;
    }
    switch (effectType) {
    case EffectType::ANTIALIASING:
    {
        if (enable) rlEnableSmoothLines();
        else        rlDisableSmoothLines();

        mFlags.antialiasingEnabled = enable;
        TraceLog(LOG_INFO, TextFormat(
        "[gfxPostProcessor] Set antialiasing effect to %i", int(enable)));
        break;
    }
    case EffectType::HEAT_DISTORT:
    {
        mFlags.heatDistortEnabled = enable;
        TraceLog(LOG_INFO, TextFormat(
        "[gfxPostProcessor] Set heat distortion effect to %i", int(enable)));
        break;
    }
    case EffectType::DISTANCE_FOG:
    {
        mFlags.distanceFogEnabled = enable;
        res::ShaderResFactory.handle
        ("PostProcessor_Shader"_hs)->setUniformInt("fogEnabled", enable ? 1 : 0);

        TraceLog(LOG_INFO, TextFormat(
        "[gfxPostProcessor] Set distance fog effect to %i", int(enable)));
        break;
    }
    default: { break; }
    }
}

void anim::gfx::PostProcessor::update()
{

}

void anim::gfx::PostProcessor::unload()
{
    if (res::ShaderResFactory.contains("PostProcessor_Shader"_hs))
        res::ShaderResFactory.unload("PostProcessor_Shader"_hs);
}

anim::gfx::PostProcessor& anim::gfx::PostProcessor::instance() {
    static PostProcessor postProcessor;
    return postProcessor;
}

const Shader* anim::gfx::PostProcessor::getShaderConst() const
{
    if (!res::ShaderResFactory.contains("PostProcessor_Shader"_hs))
        return nullptr;
    return &res::ShaderResFactory.handle("PostProcessor_Shader"_hs)->const_resource();
}

Shader* anim::gfx::PostProcessor::getShader() const
{
    if (!res::ShaderResFactory.contains("PostProcessor_Shader"_hs))
        return nullptr;
    return &res::ShaderResFactory.handle("PostProcessor_Shader"_hs)->resource();
}