/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actFlightCoin.hpp-
 *      Collectible token in the flight minigame.
 */

#pragma once
#include "Engine/Actor/actBaseActor.hpp"

namespace game::act {

class FlightCoin : public anim::act::ActorModel
{
public:
    FlightCoin(const vec3f& position, f32 value);

    void onEnter() override;
    void onUpdate() override;
    void onLeave() override;

    void setCollected(bool collected);
    f32 getNumPoints() const noexcept;

private:
    f32 mRotationAngle;
    f32 mValue;
    f32 mRotationSpeed = 1.f;
    bool isCollected = false;
};
}