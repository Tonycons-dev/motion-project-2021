/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -PlayerRemoteMotion.hpp-
 *   Calculates yaw pitch roll from accelerometer values.
 */

#include "Game/Player/PlayerActor.hpp"
#include "Engine/System/GameSystem.hpp"

void game::act::MainPlayer::getMovementMotionDevice()
{
    vec3f oldYawPitchRoll = mPlayerCamera->mYawPitchRoll;
    auto delta = anim::GameSystem::instance().getDeltaTime();

    vec3f acceleration = mMotionDevice.getAcceleration();
    acceleration.z -= 1.f;

    if (acceleration.y > 0.01f || acceleration.y < -0.01f)
        mPlayerCamera->mYawPitchRoll.x += -acceleration.y * 0.02f * delta;

    if ((acceleration.z > 0.01f || acceleration.z < -0.01f) && acceleration.z != -1.f)
        mPlayerCamera->mYawPitchRoll.y += -acceleration.z * 0.06f * delta;

    auto difference = mPlayerCamera->mYawPitchRoll.x - oldYawPitchRoll.x;
    mTiltMovement.x += difference * mTiltMultiplier;

    if (std::abs(mTiltMovement.x) > DEG2RAD * 45.f)
        mTiltMovement.x = mTiltMovement.x < 0.f ? -(DEG2RAD * 45.f) : (DEG2RAD * 45.f);

    mPlayerCamera->mYawPitchRoll = vec3f(
        (mPlayerCamera->mYawPitchRoll.x + oldYawPitchRoll.x) / 2.f,
        (mPlayerCamera->mYawPitchRoll.y + oldYawPitchRoll.y) / 2.f, 0.f);

    mInputs[INPUT_DIRECTION_F] = {mMaxInputStrength * 1.f, true};
}