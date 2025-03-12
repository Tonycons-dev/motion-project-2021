/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -MouseMgr.hpp-
 *   Functions responsible for handling mouse input.
 */

#pragma once
#include "Core/Types/BasicTypes.hpp"
#include "Core/Utils/Vector3.hpp"
#include "Core/Utils/Vector2.hpp"

namespace anim::MouseMgr
{
    struct MouseInfoData
    {
        MouseInfoData() noexcept = default;

        vec2f posDel;
        vec2f posAvg;
        vec2i posOld;
        vec2i posNew;

        f32 deltaTime = 1.0f;
    };

    enum class MouseModeType
    {
        CAPTURED, FREE
    };

    extern MouseInfoData sNewMouseInfo;
    extern MouseInfoData sOldMouseInfo;
    extern MouseModeType sMouseMode;
    extern vec2f sPosDeltaThreshold;

    void initialize();
    void update();
    void setCursorVisible(bool visible);
    void setMouseMode(MouseModeType type);

    inline void setDeltaThreshold(const vec2f& threshold) noexcept {
        sPosDeltaThreshold = threshold;
    }

    inline vec2f getPositionDelta() noexcept {
        return sNewMouseInfo.posDel;
    }

    inline vec2i getPosition() noexcept {
        return sNewMouseInfo.posNew;
    }

    inline vec2f getPositionAvg() noexcept {
        return sNewMouseInfo.posAvg;
    }
}