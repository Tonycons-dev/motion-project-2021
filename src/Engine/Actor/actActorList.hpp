/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actActorList.hpp-
 *   Defines ActorList: a structure for storing actors by numerical ID.
 */

#pragma once
#include "Engine/Actor/actBaseActor.hpp"

namespace anim::act
{

//Structure for storing actors by numerical ID.
class ActorList
{
public:
    explicit ActorList(ActorBase* owner);
    ~ActorList();

    void clear();
    void remove(u32 index);

    template<typename ActorType, typename... Args>
    u32 add(Args... args)
    {
        mChildren.insert(std::make_pair(mActorCount, new ActorType(std::forward<Args>(args)...)));

        mChildren[mActorCount]->mRoot = mOwner;
        mChildren[mActorCount]->mName = std::to_string(mActorCount).c_str();
        mChildren[mActorCount]->onCreate();

        if constexpr (std::is_base_of<ActorModel, ActorType>::value)
            ActorModelScheduler::addProcess(mChildren[mActorCount]);
        else
            ActorBaseScheduler::addProcess(mChildren[mActorCount]);

        u32 id = mActorCount; ++mActorCount;
        return id;
    }

    template<typename ActorType>
    ActorType* get(u32 index)
    {
        return (ActorType*)(mChildren[index].get());
    }

    inline u32 size() const noexcept { return mActorCount; }

    [[nodiscard]] std::unordered_map<
        u32, std::unique_ptr<ActorBase>>& getChildren() noexcept {
        return mChildren;
    }
private:
    std::unordered_map<u32, std::unique_ptr<ActorBase>> mChildren;
    ActorBase* mOwner;
    u32 mActorCount{};
};

}