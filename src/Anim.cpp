/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -Anim.cpp-
 *   Entry point of the program.
 */

#include "Engine/System/GameSystem.hpp"
#include "Game/World/worldGameWorld.hpp"

int main()	
{
    vec2u resolution(1920, 1080);

    if (anim::Runtime::isDevWorkstation1()) {
        resolution = vec2u(2048, 1152);
        LOG_MESSAGE("Running on Workstation 1");
    }

    if (anim::Runtime::isDevWorkstation2()) {
        resolution = vec2u(1920, 1080);
        LOG_MESSAGE("Running on Workstation 2");
    }

    if (!anim::GameSystem::instance().load({"AnimDemo", resolution.x, resolution.y, 165, false}))
        return -1;

	anim::act::ActorRoot::instance().addChild<game::world::GameWorld>("World");
	while (anim::GameSystem::instance().isUpdating())
	;

    anim::GameSystem::instance().unload();
    return 0;
}