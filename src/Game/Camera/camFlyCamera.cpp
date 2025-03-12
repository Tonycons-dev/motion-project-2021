/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -camFlyCamera.cpp-
 *      First person flight camera.
 */

#include "Game/Camera/camFlyCamera.hpp"
#include "Engine/System/GameSystem.hpp"
#include "Engine/System/Raymath.hpp"
#include "Core/Utils/VectorMath.hpp"


void game::cam::FlightCamera::initialize()
{
    mCamera.up         = {0.0f, 1.0f, 0.0f};
    mCamera.fovy       = 60.0f;
    mCamera.projection = CAMERA_PERSPECTIVE;
}

void game::cam::FlightCamera::update(float delta, InputData inputs[6])
{
    CameraBase::update(delta, inputs);

    f32 yc(std::cos(mYawPitchRoll.x)), ys(std::sin(mYawPitchRoll.x));
    f32 pc(std::cos(mYawPitchRoll.y)), ps(std::sin(mYawPitchRoll.y));

    vec3f direction(yc * pc, ps, ys * pc);
    direction = core::math::normalize3(direction);

    if (inputs[INPUT_DIRECTION_F].isPressed)
    {
        const auto strength = inputs[INPUT_DIRECTION_F].strength;
        setPosition(getPosition() - (direction * delta * strength));
    }

    if (inputs[INPUT_DIRECTION_B].isPressed)
    {
        const auto strength = inputs[INPUT_DIRECTION_B].strength;
        setPosition(getPosition() + (direction * delta * strength));
    }

    if (inputs[INPUT_DIRECTION_R].isPressed)
    {
        const auto strength = inputs[INPUT_DIRECTION_R].strength;

        setPosition(getPosition() - (core::math::normalize3<f32>(
            core::math::cross3<f32>(direction, *(vec3f*)(&mCamera.up))) * delta * strength));
    }

    if (inputs[INPUT_DIRECTION_L].isPressed)
    {
        const auto strength = inputs[INPUT_DIRECTION_L].strength;

        setPosition(getPosition() + (core::math::normalize3<f32>(
            core::math::cross3<f32>(direction, *(vec3f*)(&mCamera.up))) * delta * strength));
    }

    mCamera.target.x = mCamera.position.x - direction.x;
    mCamera.target.y = mCamera.position.y - direction.y;
    mCamera.target.z = mCamera.position.z - direction.z;

    mDirection = direction;
    UpdateCamera(&mCamera);
}