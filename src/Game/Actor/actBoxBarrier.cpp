/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -actBoxBarrier.cpp-
 *      Box acting as an obstacle in the flight minigame.
 */

#include "Game/Actor/actBoxBarrier.hpp"
#include "Engine/System/RaylibGL.hpp"

game::act::BarrierBox::BarrierBox(const vec3f& dimensions, const vec3f& position)
    : ActorModel(position)
{
    generateModelRectPrism(dimensions);
    setFillColor({229, 113, 113, 192});
}

void game::act::BarrierBox::onRender()
{
    DrawCubeWires({mPosition.x, mPosition.y, mPosition.z},
        mBoundingBoxSize.x, mBoundingBoxSize.y, mBoundingBoxSize.z, DARKPURPLE);
}

void game::act::BarrierBox::onEnter()
{

}

void game::act::BarrierBox::onUpdate()
{

}