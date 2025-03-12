/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -camFlyCamera.hpp-
 *      First person flight camera.
 */

#pragma once
#include "Game/Camera/camCommon.hpp"

namespace game::cam
{
    class FlightCamera : public CameraBase
    {
    public:
        void initialize() override;
        void update(float delta, InputData inputs[6]) override;
    };
}