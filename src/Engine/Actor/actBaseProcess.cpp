/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actBaseProcess.cpp-
 *   Implementation of ActorBaseProcess.
 */

#include "Engine/Actor/actBaseProcess.hpp"
#include "Engine/Actor/actBaseActor.hpp"
#include "Engine/Constants/actConstants.hpp"
#include "Engine/System/GameSystem.hpp"

entt::scheduler<s64> anim::act::ActorBaseScheduler::mScheduler;
anim::GameSystem* anim::act::ActorBaseScheduler::mEngine;

void anim::act::ActorBaseProcess::init()
{
    mActor->mProcess = this;
	mActor->mRoot->mNumProcesses++;
    mActor->onEnter();
}

void anim::act::ActorBaseProcess::update(s64 delta, void*)
{
    mRemainingTime -= std::min(mRemainingTime, delta);

    if (mRemainingTime)
        return;
    
    mRemainingTime = ACTOR_PROCESS_DELAY;
    mActor->onUpdate();
}

void anim::act::ActorBaseProcess::quit(bool immediately)
{
	mActor->mRoot->mNumProcesses--;
	abort(immediately);
}

bool anim::act::ActorBaseScheduler::addProcess(std::unique_ptr<ActorBase>& actor)
{ 
    if (mScheduler.size() > ACTOR_PROCESS_LIMIT)
        return false;

    mScheduler.attach<ActorBaseProcess>((s64)ACTOR_PROCESS_DELAY, actor);
    return true;
}