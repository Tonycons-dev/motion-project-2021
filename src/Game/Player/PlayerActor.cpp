/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -PlayerActor.cpp-
 */

#include "Game/Player/PlayerActor.hpp"
#include "Game/Player/PauseMenu.hpp"
#include "Game/Camera/camFlyCamera.hpp"
#include "Game/Camera/camPlayerCamera.hpp"
#include "Engine/System/GameSystem.hpp"

game::act::MainPlayer::MainPlayer() : ActorModel(){}

game::act::MainPlayer::MainPlayer(const vec3f& position, const vec3f& rotation)
    : ActorModel(position, rotation),

    mInputMode(InputMode::MODE_MOTION_DEVICE),
    mCameraType(CameraType::CAMERA_FIRST_PERSON),
    mCameraSensitivity(1.0f),
    mMovementSpeed    (1.0f),
    mMovementDelta    (0.0f),
    mMouseOffsetLimit (3.0f),
    mMaxInputStrength (0.01f)
{}

void game::act::MainPlayer::onEnter()
{
    addChild<PauseMenu>("PauseMenu");
    HideCursor();

    setModelResource("MainPlayer_Model"_hs);
    setModelScale(0.008f);
    //setWireframeVisible(true);

#ifdef _WIN32
    bool failure = !mMotionDevice.initialize();
    if (!failure)
        failure = !mMotionDevice.isReady();
#else
    bool failure = true;
#endif

    if (failure)
    {
        LOG_MESSAGE("Failed to initialize the motion device.");
        mInputMode = InputMode::MODE_MOUSE_POINTER;
    }
    else
    {
        mInputMode = InputMode::MODE_MOTION_DEVICE;
    }

    if (mCameraType == CameraType::CAMERA_FIRST_PERSON)
        mPlayerCamera = new cam::PlayerCamera;
    else
        mPlayerCamera = new cam::FlightCamera;

    abortIf(mPlayerCamera == nullptr, "Failed to allocate camera.");

    mPlayerCamera->mYawPitchRollLimits.y = DEG2RAD * 70.0f;
    mPlayerCamera->translate(mPosition);
    mPlayerCamera->rotate(mRotation);

    mPlayerCamera->initialize();
    mPlayerCamera->setAsCurrentCamera();

    applyCameraMovement();

    anim::MouseMgr::setMouseMode(anim::MouseMgr::MouseModeType::CAPTURED);
    anim::MouseMgr::setDeltaThreshold(vec2f(mMouseOffsetLimit));
}

void game::act::MainPlayer::onUpdate()
{
    if (getChild<PauseMenu>("PauseMenu")->isOpen())
    {
        if (mFillColor == vec4b(0, 0, 0, 0))
            mFillColor = vec4b(255, 255, 255, 255);
        return;        
    }

    if (mIsSuspended) {
        playSuspendAnimation();
        return;
    }

	if (mInputMode == InputMode::MODE_MOTION_DEVICE)
		mMotionDevice.update();

	if (mInputMode == InputMode::MODE_MOTION_DEVICE)
	    getMovementMotionDevice();
	else
	    getMovementKeyboard();

	if (IsKeyPressed(KEY_G))
        setWireframeVisible(!mRenderFlags.wireframeVisible);

	tryRecoverCamera();
    mMovementDelta = mMovementSpeed * anim::GameSystem::instance().getDeltaTime();

    mPlayerCamera->update(mMovementDelta, mInputs);
    applyCameraMovement();
}

void game::act::MainPlayer::onLeave()
{
    if (mInputMode == InputMode::MODE_MOTION_DEVICE)
        mMotionDevice.terminate();
}

void game::act::MainPlayer::setSuspended(bool suspended)
{
    mIsSuspended = suspended;

    if (!mIsSuspended && mFillColor == vec4b(0, 0, 0, 0))
        mFillColor = vec4b(255, 255, 255, 255);
}

void game::act::MainPlayer::playSuspendAnimation()
{
    static f32 suspendAnimationTime = 0.f;
    auto delta = anim::GameSystem::instance().getDeltaTime();

    suspendAnimationTime += delta;

    if (suspendAnimationTime > 24.f)
    {
        if (mFillColor == vec4b(0, 0, 0, 0))
            mFillColor = vec4b(255, 255, 255, 255);

        else if (mFillColor == vec4b(255, 255, 255, 255))
            mFillColor = vec4b(0, 0, 0, 0);

        suspendAnimationTime = 0.f;
    }
}

void game::act::MainPlayer::setPositionToSpawnpoint()
{
    const vec3f position(0.f, 0.f, 0.f);

    mPlayerCamera->setPosition(position);
    translate(position);
}