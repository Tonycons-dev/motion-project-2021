/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actActorBase.cpp-
 *   Implementation of the ActorBase class.
 */

#include <Engine/Actor/actBaseActor.hpp>
#include <Engine/Actor/actBaseProcess.hpp>
#include <Engine/System/Raylib.hpp>

namespace anim::act {

void ActorBase::onCreate(){}
void ActorBase::onEnter(){}
void ActorBase::onUpdate(){}
void ActorBase::onLeave(){}
void ActorBase::onAbort(){}
void ActorModel::onPreRender() {}
void ActorModel::onPostRender() {}


void ActorBase::removeChild(const char* name, bool abort)
{
    std::unique_ptr<ActorBase>& actor = mChildren[name];

    if (actor == nullptr)
        return;

    if (abort)
        actor->abortIf_(true);
    else
        actor->finishIf_(true);
}

void ActorBase::finishIf_(bool condition)
{
    if (condition)
    {
        endSubRoutines();
        endSubProcesses();

        mProcess->quit(false);        
    }
}

void ActorBase::abortIf_(bool condition, const char* message)
{
    if (condition)
    {
        if (message == nullptr)
            LOG_FAILURE("Aborted Actor '" << mName << "'.");
        else
            LOG_FAILURE("Aborted Actor '" << mName << "'. " << message);

        endSubRoutines();
        endSubProcesses();

        mProcess->quit(true);
    }
}

void ActorBase::endExecution()
{
    this->onLeave();
    for (auto& iter : mChildren)
        iter.second->endExecution();

    if (this->mProcess != nullptr)
        this->mProcess->quit(true);
}

void ActorBase::endSubRoutines()
{
    onLeave();
	for (auto& it : mChildren)
	    it.second->endSubRoutines();
}

void ActorBase::abortSubRoutines()
{
    onAbort();
	for (auto& it : mChildren)
	    it.second->abortSubRoutines();
}

void ActorBase::endSubProcesses()
{
	for (auto& it : mChildren) {
	    it.second->endSubProcesses();
	    it.second->mProcess->quit(true);
	}
}

void ActorBase::abortSubProcesses()
{
	for (auto& it : mChildren) {
	    it.second->abortSubRoutines();
	    it.second->mProcess->quit(true);
	}
}
}