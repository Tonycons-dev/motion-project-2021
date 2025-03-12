/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actActorList.cpp-
 *   Implementation of ActorList: a structure for storing actors by numerical ID.
 */

#include "Engine/Actor/actActorList.hpp"

anim::act::ActorList::ActorList(ActorBase *owner)
    : mOwner(owner) {}

anim::act::ActorList::~ActorList()
{
    clear();
}

void anim::act::ActorList::clear()
{
    for (auto& iter : mChildren)
        iter.second->endExecution();

    mChildren.clear();
}

void anim::act::ActorList::remove(u32 index)
{
    std::unique_ptr<ActorBase>& actor = mChildren[index];

    if (actor == nullptr)
        return;

    actor->endExecution();
    mChildren.erase(index);

    --mActorCount;
}