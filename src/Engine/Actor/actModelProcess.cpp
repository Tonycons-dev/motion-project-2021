/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actBaseProcess.cpp-
 *   Implementation of ActorModelProcess.
 */

#include "Engine/Actor/actModelProcess.hpp"
#include "Engine/Actor/actBaseActor.hpp"
#include "Engine/Constants/actConstants.hpp"
#include "Engine/System/GameSystem.hpp"
#include "Engine/Graphics/gfxPostProcessor.hpp"

entt::scheduler<s64> anim::act::ActorModelScheduler::mScheduler;
anim::GameSystem* anim::act::ActorModelScheduler::mEngine;

void anim::act::ActorModelProcess::init()
{
    if (mActor == nullptr)
        fail();
    else
    {
        mActor->mProcess = this;
        mActor->mRoot->mNumProcesses++;
        mActor->onEnter();

        auto* shader = gfx::PostProcessor::instance().getShader();

        if (shader != nullptr)
            mActor->getModelMaterial(0).shader = *shader;
    }
}

void anim::act::ActorModelProcess::update(s64 delta, void*)
{
    mRemainingTime -= std::min(mRemainingTime, delta);

    if (mRemainingTime)
        return;

    mRemainingTime = ACTOR_PROCESS_DELAY;

    mActor->onUpdate();
	mActor->onPreRender();
    mActor->onRender();

    if ((mActor->mRenderFlags.wireframeVisible || GameSystem::instance().mFlags.drawWireframe)
    && !mActor->mRenderFlags.wireframeInvisibleDebug && mActor->mRenderFlags.isModelActive)
    {
        DrawModelWires(mActor->mModel, *(Vector3*)(&mActor->mPosition),
                       mActor->mScale, *(Color*)(&mActor->mFillColor));
    }
    else if (mActor->mRenderFlags.isModelActive)
    {
        DrawModel(mActor->mModel, *(Vector3*)(&mActor->mPosition),
                  mActor->mScale, *(Color*)(&mActor->mFillColor));
    }

    if ((mActor->mRenderFlags.boundingBoxVisible || GameSystem::instance().mFlags.drawBoundingBoxes)
    && !mActor->mRenderFlags.boundingBoxInvisibleDebug && mActor->mRenderFlags.isModelActive)
    {
        auto boundingBox = mActor->getBoundingBox();

        const vec3f size(
            boundingBox.max.x - boundingBox.min.x,
            boundingBox.max.y - boundingBox.min.y,
            boundingBox.max.z - boundingBox.min.z);

        DrawCubeWires(*(Vector3*)(&mActor->mPosition), size.x, size.y, size.z, RED);
    }

    mActor->onPostRender();
}

void anim::act::ActorModelProcess::quit(bool immediately)
{
    mActor->mRoot->mNumProcesses--;
    mActor->removeModel();

    this->abort(immediately);
}

bool anim::act::ActorModelScheduler::addProcess(std::unique_ptr<ActorBase>& actor)
{
    if (mScheduler.size() > ACTOR_PROCESS_LIMIT)
        return false;

    mScheduler.attach<ActorModelProcess>((s64)ACTOR_PROCESS_DELAY, actor);
    return true;
}