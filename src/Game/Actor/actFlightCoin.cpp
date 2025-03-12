/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actFlightCoin.cpp-
 *      Collectible token in the flight minigame.
 */

#include "Game/Actor/actFlightCoin.hpp"
#include "Engine/System/GameSystem.hpp"

game::act::FlightCoin::FlightCoin(const vec3f& position, f32 value)
    :
    ActorModel(position),
    mRotationAngle(0.0f),
    mValue(value)
{}

void game::act::FlightCoin::onEnter()
{
    setModelResource("FlightCoin_Model"_hs);
    setFillColor(vec4b(212, 175, 55, 255));

    rotateXAxis(DEG2RAD * 90.f);
}

void game::act::FlightCoin::onUpdate()
{
    rotateYAxis(DEG2RAD * mRotationAngle);

    f32 delta = anim::GameSystem::instance().getDeltaTime();
    mRotationAngle += (delta * 1.35f) * mRotationSpeed;

    if (mRotationAngle >= 360.f)
        mRotationAngle = 0.f;

    if (isCollected && mScale > 0.1f)
        mScale -= (delta * 0.01f);
}

void game::act::FlightCoin::onLeave()
{

}

void game::act::FlightCoin::setCollected(bool collected)
{
    isCollected = collected;

    if (!isCollected)
        return;

    setFillColor(vec4b(255, 0, 0, 255));
    mRotationSpeed = 4.f;
}

f32 game::act::FlightCoin::getNumPoints() const noexcept
{
    return mValue * f32(!isCollected);
}