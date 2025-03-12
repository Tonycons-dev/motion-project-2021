/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -camCommon.hpp-
 */

#pragma once
#include "Core/Utils/Vector3.hpp"
#include "Engine/System/Raylib.hpp"

namespace game::cam
{
    enum InputType : int
    {
        INPUT_DIRECTION_U = 0,
        INPUT_DIRECTION_D = 1,
        INPUT_DIRECTION_L = 2,
        INPUT_DIRECTION_R = 3,
        INPUT_DIRECTION_B = 4,
        INPUT_DIRECTION_F = 5
    };

    struct InputData
    {
        float strength;
        bool isPressed;
    };

    class CameraBase
    {
    public:
        void setAsCurrentCamera();

        virtual void initialize();
        virtual void update(float delta, InputData inputs[6]);

        void rotate(const vec3f& rotation);
        void translate(const vec3f& position);

        inline vec3f getPosition() {
            return *(vec3f*)(&mCamera.position);
        }

        inline void setPosition(vec3f position) {
            mCamera.position = *(Vector3*)(&position);
        }

        Camera3D mCamera;
        vec3f mYawPitchRoll;
        vec3f mYawPitchRollLimits;
        vec3f mDirection{};
    };
}