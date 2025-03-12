/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -worldFlightMinigame.hpp-
 *   Manages the coin collecting minigame.
 */

#pragma once
#include "Engine/Actor/actBaseActor.hpp"
#include "Engine/Actor/actActorList.hpp"
#include "Core/Utils/SimplexNoise.hpp"

namespace game::world
{
class GameWorld;
class FlightMinigame : public anim::act::ActorBase
{
public:
    enum FlightPath : int
    {
        X_AXIS = 0,
        Y_AXIS = 1,
        Z_AXIS = 2
    };

    FlightMinigame() = delete;
    explicit FlightMinigame(GameWorld* world);

    void onEnter() override;
    void onUpdate() override;
    void onLeave() override;

    void generateTrajectory();
    void generateCoinsPath();
    void generateObstacleBoxes();

    vec3f getRandomCoinPlacement(s32 amount, int trajectory);
    bool isObstacleBoxTouchingCoins(const BoundingBox& box);
private:

    core::SimplexNoise mNoise;

    anim::act::ActorList mCoins;
    anim::act::ActorList mBoxes;

    std::vector<vec3f> mPositions;
    GameWorld* mWorld;

    vec3f mLocation;
    vec3f mDimensions;

    FlightPath mTrajectory{};
    f32 mScore{};
};

}