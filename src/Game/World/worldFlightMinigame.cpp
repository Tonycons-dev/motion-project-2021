/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -worldFlightMinigame.cpp-
 *   Manages the coin collecting minigame.
 */

#include "Game/World/worldFlightMinigame.hpp"
#include "Game/World/worldGameWorld.hpp"
#include "Game/Player/PlayerActor.hpp"
#include "Game/Actor/actFlightCoin.hpp"
#include "Game/Actor/actBoxBarrier.hpp"
#include "Core/Utils/VectorMath.hpp"
#include "Core/Utils/RandomValue.hpp"


game::world::FlightMinigame::FlightMinigame(GameWorld *world)
    :
    anim::act::ActorBase(),
    mNoise(GetRandomValue(0x0000, 0xffff)),
    mCoins(this),
    mBoxes(this),
    mWorld(world),
    mDimensions(96.f, 32.f, 96.f)
{}

void game::world::FlightMinigame::onEnter()
{
    abortIf(mWorld == nullptr, "Minigame world is nullptr")

    abortIf(mWorld->getChild<act::MainPlayer>("MainPlayer") == nullptr,
             "Minigame world does not contain a player.")

    auto playerPos = mWorld->getChild<act::MainPlayer>("MainPlayer")->mPosition;

    mLocation.x = playerPos.x - (mDimensions.x / 2.f);
    mLocation.y = playerPos.y;
    mLocation.z = playerPos.z - (mDimensions.z / 2.f);

    mTrajectory = FlightPath::X_AXIS;

    for (int i = 0; i < 12; i++)
    {
        if (mTrajectory == FlightPath::X_AXIS)
            mTrajectory = FlightPath::Z_AXIS;

        else if (mTrajectory == FlightPath::Z_AXIS)
            mTrajectory = FlightPath::X_AXIS;

        this->generateTrajectory();
        this->generateCoinsPath();
    }

    this->generateObstacleBoxes();
}

void game::world::FlightMinigame::onUpdate()
{
    auto player = mWorld->getChild<act::MainPlayer>("MainPlayer");

    for (auto& iter : mCoins.getChildren())
    {
        auto coin = (act::FlightCoin*)iter.second.get();

        if (core::math::distance(player->mPosition, coin->mPosition) > 5.0f
        || core::math::distance(player->mPosition, coin->mPosition) < -5.0f)
            continue;

        if (CheckCollisionBoxes(player->getBoundingBox(), coin->getBoundingBox()))
        {
            mScore += coin->getNumPoints();
            coin->setCollected(true);
        }
    }

    DrawText(TextFormat("Score: %f points", mScore), 96, 64, 20, RED);

    for (auto& iter : mBoxes.getChildren())
    {
        auto rect = (act::BarrierBox*)iter.second.get();

        if (core::math::distance(player->mPosition, rect->mPosition) > 32.f
        || core::math::distance(player->mPosition, rect->mPosition) < -32.0f)
            continue;

        if (CheckCollisionBoxes(player->getBoundingBox(), rect->getBoundingBox()))
            mWorld->getChild<act::MainPlayer>("MainPlayer")->setSuspended(true);
    }
}

void game::world::FlightMinigame::onLeave()
{

}

void game::world::FlightMinigame::generateTrajectory()
{
    s32 maxPositions = core::getRandomInt(10, 50);
    vec3f position = getRandomCoinPlacement(maxPositions, mTrajectory);

    mPositions.clear();
    mPositions.reserve(u32(maxPositions));

    f32 n = core::getRandomFloat(0.f, 100.f);

    for (s32 i = 0; i < maxPositions; i++)
    {
        f32 val = n * 0.1f;
        
        auto v1 = f32(mNoise.eval(val, val, val));
        auto v2 = f32(mNoise.eval(-val, -val, -val));

        auto dx = std::sin((n + v2) * 0.16f) * 4.f;
        auto dy = std::sin((-n + v1) * 0.16f) * 4.f;

        if (mTrajectory == FlightPath::X_AXIS)
            mPositions.emplace_back(vec3f(
                position.x + f32(i), position.y + dy, position.z + dx));

        else if (mTrajectory == FlightPath::Z_AXIS)
            mPositions.emplace_back(vec3f(
                position.x + dx, position.y + dy, position.z + f32(i)));

        n += 2.5f;
    }
}

void game::world::FlightMinigame::generateCoinsPath()
{
    f32 value = 0.f;
    for (const auto& position : mPositions)
    {
        auto npoints = 1.f + (++value / 4.f);
        auto id = mCoins.add<act::FlightCoin>(position, npoints);

        if (mTrajectory == FlightPath::Z_AXIS)
            mCoins.get<act::FlightCoin>(id)->rotateYAxis(DEG2RAD * 90.f);
    }
}

vec3f game::world::FlightMinigame::getRandomCoinPlacement(s32 amount, int direction)
{
    vec3f position = mLocation;

    for (int i = 0; i < 3; i++)
        position[i] += core::getRandomFloat(0.f, mDimensions[i]);

    if (direction == FlightPath::X_AXIS)
        while ((position.x + f32(amount)) > (position.x + mDimensions.x))
            --position.x;

    if (direction == FlightPath::Z_AXIS)
        while ((position.z + f32(amount)) > (position.z + mDimensions.z))
            --position.z;

    return position;
}

void game::world::FlightMinigame::generateObstacleBoxes()
{
    for (int i = 0; i < 32; i++)
    {
        vec3f dimensions, coordinates;

        for (int n = 0; n < 3; n++)
            dimensions[n] = core::getRandomFloat(1.f, 15.f);

        for (int n = 0; n < 3; n++)
            coordinates[n] = mLocation[n] + core::getRandomFloat(0.f, mDimensions[n]);

        auto boundingBox = BoundingBox {
        { 
            coordinates.x - dimensions.x / 2.f,
            coordinates.y - dimensions.y / 2.f,
            coordinates.z - dimensions.z / 2.f},
        {
            coordinates.x + dimensions.x / 2.f,
            coordinates.y + dimensions.y / 2.f,
            coordinates.z + dimensions.z / 2.f},
        };

        if (!isObstacleBoxTouchingCoins(boundingBox) &&
            !CheckCollisionBoxes(boundingBox, GameWorld::getSpawnpointBoundingBox()))
            mBoxes.add<act::BarrierBox>(dimensions, coordinates);
    }
}

bool game::world::FlightMinigame::isObstacleBoxTouchingCoins(const BoundingBox& box)
{
    for (const auto& iter : mCoins.getChildren())
    {
        auto coin = (act::FlightCoin*)(iter.second.get());

        if (CheckCollisionBoxes(box, coin->getBoundingBox()))
            return true;
    }
    return false;
}