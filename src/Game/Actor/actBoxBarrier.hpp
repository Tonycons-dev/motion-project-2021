/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actBoxBarrier.hpp-
 *      Box acting as an obstacle in the flight minigame.
 */

#pragma once
#include "Engine/Actor/actBaseActor.hpp"

namespace game::act {

class BarrierBox : public anim::act::ActorModel
{
public:
    BarrierBox(const vec3f& dimensions, const vec3f& position);

    void onRender() override;
    void onEnter() override;
    void onUpdate() override;
};
}