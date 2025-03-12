/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -MouseMgr.cpp-
 *   Functions responsible for handling mouse input.
 */

#include "Engine/System/MouseMgr.hpp"
#include "Engine/System/Raylib.hpp"
#include "Engine/System/GameSystem.hpp"

namespace anim::MouseMgr
{
    MouseInfoData sNewMouseInfo;
    MouseInfoData sOldMouseInfo;
    MouseModeType sMouseMode = MouseModeType::FREE;
    vec2f sPosDeltaThreshold(5.0f, 5.0f);
}

void anim::MouseMgr::initialize()
{
    sNewMouseInfo.deltaTime = GameSystem::instance().getDeltaTime();
    sOldMouseInfo = sNewMouseInfo;

    setCursorVisible(true);
    setMouseMode(MouseModeType::FREE);
}

void anim::MouseMgr::update()
{
    sNewMouseInfo.deltaTime = GameSystem::instance().getDeltaTime();
    auto currentMousePosition_ = GetMousePosition();

    sNewMouseInfo.posNew.x = s32(currentMousePosition_.x);
    sNewMouseInfo.posNew.y = s32(currentMousePosition_.y);

    sNewMouseInfo.posAvg.x = f32(sNewMouseInfo.posNew.x + sNewMouseInfo.posOld.x) / 2.f;
    sNewMouseInfo.posAvg.y = f32(sNewMouseInfo.posNew.y + sNewMouseInfo.posOld.y) / 2.f;

    sNewMouseInfo.posDel = (vec2f)sNewMouseInfo.posAvg - (vec2f)sNewMouseInfo.posOld;
    sNewMouseInfo.posDel = (sNewMouseInfo.posDel + sOldMouseInfo.posDel) / 2.f;

    if (sNewMouseInfo.posDel.x < 0.f && sNewMouseInfo.posDel.x < -sPosDeltaThreshold.x)
        sNewMouseInfo.posDel.x = -sPosDeltaThreshold.x;

    if (sNewMouseInfo.posDel.x > 0.f && sNewMouseInfo.posDel.x > sPosDeltaThreshold.x)
        sNewMouseInfo.posDel.x = sPosDeltaThreshold.x;

    if (sNewMouseInfo.posDel.y < 0.f && sNewMouseInfo.posDel.y < -sPosDeltaThreshold.y)
        sNewMouseInfo.posDel.y = -sPosDeltaThreshold.y;

    if (sNewMouseInfo.posDel.y > 0.f && sNewMouseInfo.posDel.y > sPosDeltaThreshold.y)
        sNewMouseInfo.posDel.y = sPosDeltaThreshold.y;

    sNewMouseInfo.posOld = sNewMouseInfo.posNew;
    sOldMouseInfo = sNewMouseInfo;
}

void anim::MouseMgr::setCursorVisible(bool visible)
{
    if (visible)
        ShowCursor();
    else
        HideCursor();
}

void anim::MouseMgr::setMouseMode(MouseModeType type)
{
    sMouseMode = type;
    if (sMouseMode == MouseModeType::CAPTURED)
        DisableCursor();
    else
        EnableCursor();
}