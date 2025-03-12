/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -PlayerKeyboardMotion.cpp-
 *   Calculates yaw, pitch, roll, and movement from mouse and keyboard input.
 */

#include "Game/Player/PlayerActor.hpp"
#include "Game/Player/PauseMenu.hpp"
#include "Engine/System/GameSystem.hpp"

void game::act::MainPlayer::getMovementKeyboard()
{
    vec2f offset = -anim::MouseMgr::getPositionDelta();
    offset *= (mCameraSensitivity * mMovementDelta);

    if (offset.x < -mMouseOffsetLimit)
        offset.x = -mMouseOffsetLimit;

    else if (offset.x > mMouseOffsetLimit)
        offset.x = mMouseOffsetLimit;

    if (offset.y < -mMouseOffsetLimit)
        offset.y = -mMouseOffsetLimit;

    else if (offset.y > mMouseOffsetLimit)
        offset.y = mMouseOffsetLimit;

    mPlayerCamera->mYawPitchRoll += {-offset.x, -offset.y, 0.0f};
    auto* pauseMenu = getChild<PauseMenu>("PauseMenu");

    for (u32 idx = 0; idx < 6; idx++)
    {
        bool move = IsKeyDown(pauseMenu->getPlayerInputBindings()[idx]);
        mInputs[idx] = {mMaxInputStrength * f32(move), move};
    }
}