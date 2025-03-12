/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -PlayerActor.hpp-
 */

#pragma once
#include "Engine/Actor/actBaseActor.hpp"
#include "Engine/IO/remoteDevice.hpp"
#include "Game/Camera/camCommon.hpp"

namespace game::act {

class MainPlayer : public anim::act::ActorModel
{
public:
    enum class InputMode : int
    {
        MODE_MOTION_DEVICE,
        MODE_CONTROLLER,
        MODE_MOUSE_POINTER
    };

    enum InputType : int
    {
        INPUT_DIRECTION_U = 0,
        INPUT_DIRECTION_D = 1,
        INPUT_DIRECTION_L = 2,
        INPUT_DIRECTION_R = 3,
        INPUT_DIRECTION_B = 4,
        INPUT_DIRECTION_F = 5
    };

    enum CameraRecoverType : int
    {
        INFINITE_ANGLES,
        EXCEEDED_ANGLES,
        OUT_OF_BOUNDS,
        MANUAL_RECOVERY,
        NONE
    };

    enum CameraType : int
    {
        CAMERA_FLIGHT,
        CAMERA_FIRST_PERSON
    };

    MainPlayer();
    MainPlayer(const vec3f& position, const vec3f& rotation);

    void onEnter() override;
    void onUpdate() override;
    void onLeave() override;

    void changeCamera(CameraType cameraType);
    void setSuspended(bool suspended);
    void playSuspendAnimation();
    void setPositionToSpawnpoint();

	[[nodiscard]] CameraRecoverType shouldRecoverCamera() const;
	void tryRecoverCamera();

    inline bool isSuspended() const noexcept { return mIsSuspended; }
private:
    cam::CameraBase* mPlayerCamera{};
    cam::InputData mInputs[6]{};

	void getMovementKeyboard();
	void getMovementMotionDevice();
	void applyCameraMovement();

    anim::RemoteDevice mMotionDevice;

    vec3f mVelocityDeadZone{0.1f, 0.1f, 0.1f};
    vec3f mAccelerationDeadZone{0.02f, 0.02f, 0.02f};

    InputMode mInputMode = InputMode::MODE_MOTION_DEVICE;
    CameraType mCameraType = CameraType::CAMERA_FLIGHT;

    f32 mCameraSensitivity  = 0.008f;
    f32 mMovementSpeed      = 1.0f;
	f32 mMovementDelta      = 0.0f;
    f32 mMouseOffsetLimit   = 5.0f;
    f32 mMaxInputStrength   = 0.01f;

    vec2f mTiltMovement{};
    f32 mTiltMultiplier = 1.f;
    bool mIsSuspended = false;
};
}