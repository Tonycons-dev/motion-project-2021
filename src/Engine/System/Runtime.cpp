#include "Engine/System/Runtime.hpp"
#include "Engine/System/Raylib.hpp"
#include "Engine/Resource/resFilesystem.hpp"
#include "Engine/Resource/resBasicTagParser.hpp"
#include "Engine/Resource/resTextResource.hpp"

anim::Runtime::ConfigData anim::Runtime::loadDefaultConfigData()
{
    return ConfigData
    {
        .effectFlags = gfx::PostProcessor::EffectFlags
        {
            .antialiasingEnabled = false,
            .distanceFogEnabled = true,
            .heatDistortEnabled = false,
        },
        .gameWindowTitle = "Ceru",
        .gameWindowSizeX = u32(GetMonitorWidth(GetCurrentMonitor())),
        .gameWindowSizeY = u32(GetMonitorHeight(GetCurrentMonitor())),
        .targetFramerate = u32(GetMonitorRefreshRate(GetCurrentMonitor())),
        .fullscreen = true,
        .disableSerial = true,
    };
}

void anim::Runtime::loadConfigData()
{
    const auto configDefault = loadDefaultConfigData();
    if (!res::Filesystem::pathExists("configs/runtime_config.txt")) {
        mConfigData = configDefault;
        return;
    }
    auto handle = res::TextResFactory.load(
        "RuntimeConfig"_hs, "configs/runtime_config.txt");

    if (!handle->isResourceValid()) {
        mConfigData = configDefault;
        return;
    }
    res::BasicTagParser parser(7, handle->const_resource());

    auto gameWindowTitle = parser.getStringValue("gameWindowTitle");
    mConfigData.gameWindowTitle = gameWindowTitle.invalid ?
    configDefault.gameWindowTitle : gameWindowTitle.value;

    loadConfigDataValueUint(parser, mConfigData.gameWindowSizeX,
        configDefault.gameWindowSizeX, 0, "gameWindowSizeX");

    loadConfigDataValueUint(parser, mConfigData.gameWindowSizeY,
        configDefault.gameWindowSizeY, 0, "gameWindowSizeY");

    loadConfigDataValueUint(parser, mConfigData.targetFramerate,
        configDefault.targetFramerate, 0, "gameTargetFrame");

    const auto gameFullscreen = parser.getIntValue("gameFullscreen");
    if (gameWindowTitle.invalid)
        mConfigData.fullscreen = configDefault.fullscreen;
    else {
        if (gameFullscreen.value == 0)
            mConfigData.fullscreen = configDefault.fullscreen;
        else mConfigData.fullscreen = gameFullscreen.value;
    }

    auto doAntialiasing = parser.getIntValue("doAntialiasing");
    mConfigData.effectFlags.antialiasingEnabled = doAntialiasing.invalid ?
    configDefault.effectFlags.antialiasingEnabled : doAntialiasing.value != 0;

    auto disableSerPort = parser.getIntValue("disableSerPort");
    mConfigData.disableSerial = disableSerPort.invalid ?
    configDefault.disableSerial : disableSerPort.value != 0;
}

void anim::Runtime::loadConfigDataValueUint(const res::BasicTagParser& parser,
    u32& data, const u32& defaultValue, u32 delimiter, const char* parameterName)
{
    const auto tagParameter = parser.getIntValue(parameterName);
    if (tagParameter.invalid)
        data = defaultValue;
    else {
        if (tagParameter.value == delimiter) data = defaultValue;
        else data = tagParameter.value;
    }
}