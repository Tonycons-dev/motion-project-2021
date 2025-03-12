#pragma once
#include "Core/Types/BasicTypes.hpp"
#include "Engine/Graphics/gfxPostProcessor.hpp"
#include "Engine/Resource/resBasicTagParser.hpp"

namespace anim::Runtime
{
    struct ConfigData
    {
        gfx::PostProcessor::EffectFlags effectFlags{};

        const char* gameWindowTitle{};
        u32 gameWindowSizeX{};
        u32 gameWindowSizeY{};
        u32 targetFramerate{};
        bool fullscreen{};
        bool disableSerial{};
    };

    extern ConfigData mConfigData;

    void loadConfigData();
    ConfigData loadDefaultConfigData();

    void loadConfigDataValueUint(const res::BasicTagParser& parser,
        u32& data, const u32& defaultValue, u32 delimiter, const char* parameterName);

    u32 getNumThreads();
    bool isDevWorkstation1();
    bool isDevWorkstation2();
}