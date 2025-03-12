/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -camPlayerCamera.hpp-
 *      First person Minecraft-esque camera
 */

#pragma once
#include "Game/Camera/camCommon.hpp"

namespace game::cam
{
    class PlayerCamera : public CameraBase
    {
    public:
        void initialize() override;
        void update(float delta, InputData inputs[6]) override;
    };
}