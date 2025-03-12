/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actProcess.hpp-
 */

#pragma once

#include <Core/Types/BasicTypes.hpp>
#include <entt/entt.hpp>

namespace anim { class GameSystem; }
namespace anim::act {

class ActorBase;
class ActorProcess
{
public:
    using delta_type = s64;
	ActorProcess(delta_type delay) : mRemainingTime(delay) {};

    virtual void update(delta_type delta, void*);
    virtual void init();
    virtual void quit(bool immediately);

protected:
    delta_type mRemainingTime;
};
}