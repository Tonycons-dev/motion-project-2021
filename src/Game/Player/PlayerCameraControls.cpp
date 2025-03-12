/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -PlayerCameraControls.cpp-
 *   Handles updating of camera and model.
 */

#include "Game/Player/PlayerActor.hpp"
#include "Game/Camera/camPlayerCamera.hpp"
#include "Game/Camera/camFlyCamera.hpp"
#include "Engine/System/Raymath.hpp"

void game::act::MainPlayer::applyCameraMovement()
{
    translate(mPlayerCamera->getPosition() + (-mPlayerCamera->mDirection * 3.f));
    translate(vec3f(mPosition.x, mPosition.y - 1.f, mPosition.z));

    rotateOnXYZ(vec3f(-mPlayerCamera->mYawPitchRoll.y,
        mPlayerCamera->mYawPitchRoll.x + (DEG2RAD * 90.f), 0.f));
}

game::act::MainPlayer::CameraRecoverType
game::act::MainPlayer::shouldRecoverCamera() const
{
    if (IsKeyPressed(KEY_R))
        return CameraRecoverType::MANUAL_RECOVERY;

    if (std::isnan(mPlayerCamera->mYawPitchRoll.x)
     || std::isnan(mPlayerCamera->mYawPitchRoll.y)
     || std::isnan(mPlayerCamera->mYawPitchRoll.z))
        return CameraRecoverType::INFINITE_ANGLES;

    if (mPlayerCamera->mYawPitchRoll.y > mPlayerCamera->mYawPitchRollLimits.y
    || mPlayerCamera->mYawPitchRoll.y < -mPlayerCamera->mYawPitchRollLimits.y)
        return CameraRecoverType::EXCEEDED_ANGLES;

    return CameraRecoverType::NONE;
}

void game::act::MainPlayer::tryRecoverCamera()
{
    CameraRecoverType recoverType = this->shouldRecoverCamera();

    if (recoverType == CameraRecoverType::NONE)
        return;

    if (recoverType == CameraRecoverType::EXCEEDED_ANGLES)
    {
        if (mPlayerCamera->mYawPitchRoll.y < 0.f)
            mPlayerCamera->mYawPitchRoll.y = -mPlayerCamera->mYawPitchRollLimits.y;

        else if (mPlayerCamera->mYawPitchRoll.y > 0.f)
            mPlayerCamera->mYawPitchRoll.y = mPlayerCamera->mYawPitchRollLimits.y;
    }
    else if (recoverType == CameraRecoverType::INFINITE_ANGLES)
    {
        const vec3f _yawPitchRoll = mPlayerCamera->mYawPitchRoll;
        mPlayerCamera->mYawPitchRoll = vec3f(0.0f, 0.0f, 0.0f);

        LOG_MESSAGE(TextFormat(
        "Recovered camera. Previous yaw pitch roll: %04.04f %04.04f %04.04f",
        _yawPitchRoll.x, _yawPitchRoll.y, _yawPitchRoll.z));
    }
    else
    {
        mPlayerCamera->initialize();
        const vec3f _yawPitchRoll = mPlayerCamera->mYawPitchRoll;

        mPlayerCamera->mYawPitchRoll = vec3f(0.0f, 0.0f, 0.0f);
        mPlayerCamera->setAsCurrentCamera();

        LOG_MESSAGE(TextFormat(
        "Recovered camera manually. Previous yaw pitch roll: %04.04f %04.04f %04.04f",
       _yawPitchRoll.x, _yawPitchRoll.y, _yawPitchRoll.z));
    }
}

void game::act::MainPlayer::changeCamera(CameraType cameraType)
{
    if (cameraType == mCameraType)
        return;

    mCameraType = cameraType;

    Camera3D camera3D{};
    vec3f yawPitch;

    if (mPlayerCamera != nullptr)
    {
        camera3D = mPlayerCamera->mCamera;
        yawPitch = mPlayerCamera->mYawPitchRoll;

        delete mPlayerCamera;
    }

    if (mCameraType == CameraType::CAMERA_FIRST_PERSON)
        mPlayerCamera = new cam::PlayerCamera;
    else
        mPlayerCamera = new cam::FlightCamera;

    abortIf_(mPlayerCamera == nullptr, "Failed to allocate camera.");

    mPlayerCamera->mCamera = camera3D;
    mPlayerCamera->mYawPitchRoll = yawPitch;
    mPlayerCamera->mYawPitchRollLimits.y = DEG2RAD * 70.0f;

    mPlayerCamera->setAsCurrentCamera();
}