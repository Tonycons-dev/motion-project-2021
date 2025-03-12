/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actBaseProcess.cpp-
 *   Handles the updating of actors derived from ActorModel.
 */

#pragma once
#include "Engine/Actor/actProcess.hpp"

namespace anim::act {

class ActorModel;
class ActorModelProcess: public ActorProcess, public entt::process<ActorModelProcess, s64>
{
public:
	ActorModelProcess(s64 delay, std::unique_ptr<ActorBase>& actor)
		: ActorProcess(delay), mActor((ActorModel*)actor.get()) {}

    void update(s64 delta, void*) override;
    void init() override;

    void quit(bool immediately) override;
private:
	ActorModel* mActor = nullptr;
};

class ActorModelScheduler
{
public:
    static bool addProcess(std::unique_ptr<ActorBase>& actor);

    inline static void updateProcesses(const s64 delta) {
        mScheduler.update(delta);
    }

    inline static void setEngine(anim::GameSystem* engine) {
        mEngine = engine == nullptr ? mEngine : engine;
    }
    inline static anim::GameSystem* getEngine() noexcept {
        return mEngine;
    }
private:
    static entt::scheduler<s64> mScheduler;
    static anim::GameSystem* mEngine;
};
}