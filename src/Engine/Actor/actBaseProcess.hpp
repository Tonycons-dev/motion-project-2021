/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actBaseProcess.hpp-
 *   Handles the updating of actors derived from ActorBase.
 */

#pragma once
#include "Engine/Actor/actProcess.hpp"

namespace anim::act {

class ActorBaseProcess: public ActorProcess, public entt::process<ActorBaseProcess, s64>
{
public:
	ActorBaseProcess(s64 delay, std::unique_ptr<ActorBase>& actor)
		: ActorProcess(delay), mActor(actor) {}

    void update(s64 delta, void*) override;
    void init() override;

    void quit(bool immediately) override;
private:
	std::unique_ptr<ActorBase>& mActor;
};

class ActorBaseScheduler
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