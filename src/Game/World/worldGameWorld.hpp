/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -worldGameWorld.hpp-
 *   Root of events in the game world.
 */

#pragma once
#include "Engine/Actor/actBaseActor.hpp"

namespace game::world
{
class GameWorld : public anim::act::ActorBase
{
public:
    void onEnter() override;
    void onUpdate() override;
    void onLeave() override;

    static BoundingBox getSpawnpointBoundingBox() noexcept;
};
}