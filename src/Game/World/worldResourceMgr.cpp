#include "Game/World/worldResourceMgr.hpp"
#include "Engine/Actor/actBaseActor.hpp"

void game::world::ResourceMgr::loadResources()
{
    using namespace anim::act;

    ActorModel::createModelResourceRectPrism("MainPlayer_Model"_hs, {0.1f, 0.1f, 0.1f});
    ActorModel::createModelResourceCylinder("FlightCoin_Model"_hs, 0.3f, 0.08f, 16);

    LOG_MESSAGE("[WorldResourceMgr] Loaded resources.");
}

void game::world::ResourceMgr::unloadResources()
{
    using namespace anim::act;

    ActorModel::unloadModelResource("MainPlayer_Model"_hs);
    ActorModel::unloadModelResource("FlightCoin_Model"_hs);

    LOG_MESSAGE("[WorldResourceMgr] Unloaded resources.");
}