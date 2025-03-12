/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actBaseProcess.cpp-
 *   Implementation of the single function which ActorRoot requires.
 */

#include <Engine/Actor/actRootActor.hpp>

anim::act::ActorRoot& anim::act::ActorRoot::instance()
{
    static ActorRoot root;
    return root;
}