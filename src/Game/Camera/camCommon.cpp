/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -camCommon.cpp-
 */

#include "Game/Camera/camCommon.hpp"
#include "Engine/System/GameSystem.hpp"
#include "Engine/System/Raymath.hpp"
#include "Core/Utils/VectorMath.hpp"


void game::cam::CameraBase::setAsCurrentCamera()
{
    anim::GameSystem::instance().setCameraPtr(&mCamera);
    SetCameraMode(mCamera, CAMERA_CUSTOM);
}

void game::cam::CameraBase::initialize()
{
    mCamera.position   = {1.0f, 5.0f, 1.0f};
    mCamera.target     = {0.0f, 3.0f, 0.0f};
    mCamera.up         = {0.0f, 1.0f, 0.0f};
    mCamera.fovy       = 60.0f;
    mCamera.projection = CAMERA_PERSPECTIVE;
}

void game::cam::CameraBase::translate(const vec3f& position)
{
    mCamera.position = *(Vector3*)(&position);
}

void game::cam::CameraBase::rotate(const vec3f& rotation)
{
    vec3f position = *(vec3f*)(&mCamera.position);
    vec3f target = position - rotation;

    mCamera.target = *(Vector3*)(&target);
}

void game::cam::CameraBase::update(float delta, InputData inputs[6])
{
    for (u32 i = 0; i < 3; i++)
    {
        if (mYawPitchRollLimits[i] != 0.0f)
        {
            if (mYawPitchRoll[i] > mYawPitchRollLimits[i])
                mYawPitchRoll[i] = mYawPitchRollLimits[i];

            else if (mYawPitchRoll[i] < -mYawPitchRollLimits[i])
                mYawPitchRoll[i] = -mYawPitchRollLimits[i];
        }
    }

    for (u32 i = 0; i < 6; i++)
    {
        if (inputs[i].strength > 1.0f)
            inputs[i].strength = 1.0f;
    }
}