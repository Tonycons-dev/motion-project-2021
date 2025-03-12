/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -camPlayerCamera.cpp-
 */

#include "Game/Camera/camPlayerCamera.hpp"
#include "Engine/System/GameSystem.hpp"
#include "Engine/System/Raymath.hpp"
#include "Core/Utils/VectorMath.hpp"

void game::cam::PlayerCamera::initialize()
{
    mCamera.up         = {0.0f, 1.0f, 0.0f};
    mCamera.fovy       = 60.0f;
    mCamera.projection = CAMERA_PERSPECTIVE;
}

void game::cam::PlayerCamera::update(f32 delta, InputData inputs[6])
{
    CameraBase::update(delta, inputs);

    f32 yc(std::cos(mYawPitchRoll.x)), ys(std::sin(mYawPitchRoll.x));
    f32 pc(std::cos(mYawPitchRoll.y)), ps(std::sin(mYawPitchRoll.y));

    f32 fp(std::cos(DEG2RAD * 45.0f));

    vec3f direction1(core::math::normalize3<float>({yc * pc, ps, ys * pc}));
    vec3f direction2(core::math::normalize3<float>({yc * fp, ps, ys * fp}));

    f32 lastY = getPosition().y;

    if (inputs[InputType::INPUT_DIRECTION_F].isPressed)
    {
        auto strength = inputs[InputType::INPUT_DIRECTION_F].strength;
        setPosition(getPosition() - (direction2 * delta * strength));
    }

    if (inputs[InputType::INPUT_DIRECTION_B].isPressed)
    {
        auto strength = inputs[InputType::INPUT_DIRECTION_B].strength;
        setPosition(getPosition() + (direction2 * delta * strength));
    }

    mCamera.position.y = lastY;

    if (inputs[InputType::INPUT_DIRECTION_D].isPressed)
    {
        f32 strength = inputs[InputType::INPUT_DIRECTION_D].strength;
        mCamera.position.y -= delta * strength;
    }

    if (inputs[InputType::INPUT_DIRECTION_U].isPressed)
    {
        f32 strength = inputs[InputType::INPUT_DIRECTION_U].strength;
        mCamera.position.y += delta * strength;
    }

    if (inputs[InputType::INPUT_DIRECTION_R].isPressed)
    {
        f32 strength = inputs[InputType::INPUT_DIRECTION_R].strength;

        setPosition(getPosition() - (core::math::normalize3<f32>(
            core::math::cross3<f32>(direction1, *(vec3f*)(&mCamera.up))) * delta * strength));
    }

    if (inputs[InputType::INPUT_DIRECTION_L].isPressed)
    {
        f32 strength = inputs[InputType::INPUT_DIRECTION_L].strength;

        setPosition(getPosition() + (core::math::normalize3<f32>(
            core::math::cross3<f32>(direction1, *(vec3f*)(&mCamera.up))) * delta * strength));
    }

    if ((getPosition().y < lastY) && !inputs[InputType::INPUT_DIRECTION_D].isPressed)
        mCamera.position.y = lastY;

    if ((getPosition().y > lastY) && !inputs[InputType::INPUT_DIRECTION_U].isPressed)
        mCamera.position.y = lastY;

    mCamera.target.x = mCamera.position.x - direction1.x;
    mCamera.target.y = mCamera.position.y - direction1.y;
    mCamera.target.z = mCamera.position.z - direction1.z;

    mDirection = direction1;
    UpdateCamera(&mCamera);
}