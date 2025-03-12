/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actRootActor.cpp-
 *   Defines the top-level actor which is always active.
 *   It has no behavior and only exists as a container for other actors to be added.
 */

#pragma once
#include <Engine/Actor/actBaseActor.hpp>

namespace anim { class GameSystem; }
namespace anim::act {

class ActorRoot : public ActorBase
{
public:
    static ActorRoot& instance();

    ActorRoot(const ActorRoot&) = delete;
    ActorRoot(const ActorRoot&&) = delete;
private:
    ActorRoot() = default;
};
}