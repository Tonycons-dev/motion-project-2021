/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -worldGameWorld.cpp-
 *   Root of events in the game world.
 */

#include "Game/World/worldGameWorld.hpp"
#include "Game/World/worldFlightMinigame.hpp"
#include "Game/World/worldResourceMgr.hpp"
#include "Game/Actor/actWorldSkybox.hpp"
#include "Game/Player/PlayerActor.hpp"
#include "Engine/Graphics/gfxWorldview.hpp"
#include "Engine/System/GameSystem.hpp"

void game::world::GameWorld::onEnter()
{
    world::ResourceMgr::loadResources();

    anim::gfx::WorldView::isWorldGridShown   = true;
    anim::gfx::WorldView::isWorldOriginShown = true;

    anim::gfx::WorldView::addDebugBoundingBox(getSpawnpointBoundingBox());

    const char* skyboxShaderDirectories[4] = {
        SHADER_PATH("vs_%i_skybox.shader"), SHADER_PATH("fs_%i_skybox.shader"),
        SHADER_PATH("vs_%i_cubeMap.shader"), SHADER_PATH("fs_%i_cubeMap.shader"),
    };

    addChild<game::act::Skybox>("Skybox",
        skyboxShaderDirectories, IMAGE_PATH("skybox.png"), false);

    addChild<game::act::MainPlayer>("MainPlayer");
    addChild<game::world::FlightMinigame>("Minigame", this);
}

void game::world::GameWorld::onUpdate()
{
    if (IsKeyPressed(KEY_F))
    {
        MaximizeWindow();
        ToggleFullscreen();
    }
    using GameSys = anim::GameSystem;

    if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_B))
        GameSys::instance().mFlags.drawBoundingBoxes = !GameSys::instance().mFlags.drawBoundingBoxes;

    if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_V))
        GameSys::instance().mFlags.drawWireframe = !GameSys::instance().mFlags.drawWireframe;

    auto* player = getChild<act::MainPlayer>("MainPlayer");

    if (IsKeyPressed(KEY_T) && player->isSuspended())
    {
        player->setSuspended(false);
        player->setPositionToSpawnpoint();
    }

    if (player->isSuspended())
    {
        auto center = GameSys::instance().getWindowCenter();
        DrawText("Game Over. Press T to restart!", center.x - 20, center.y - 20, 32, PURPLE);
    }
}

void game::world::GameWorld::onLeave()
{
    world::ResourceMgr::unloadResources();
}

BoundingBox game::world::GameWorld::getSpawnpointBoundingBox() noexcept
{
    return BoundingBox {
        { -5.f - 10.f / 2.f, 5.f + 10.f / 2.f, -5.f - 10.f / 2.f},
        { -5.f + 10.f / 2.f, 5.f - 10.f / 2.f, -5.f + 10.f / 2.f}};
}