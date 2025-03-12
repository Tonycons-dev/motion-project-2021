///* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
// *
// * -actFlightRing.cpp-
// *      Unfinished flight minigame item.
// */
//
//#include "Game/Actor/actFlightRing.hpp"
//
//game::act::FlightRing::FlightRing(
//    const vec3f& position, const vec3f& rotation, f32 diameter, f32 value)
//    :
//    ActorModel(position, rotation),
//    mDiameter(diameter)
//{}
//
//void game::act::FlightRing::onEnter()
//{
//    f32 radius = mDiameter * 0.5f;
//
//    mModel = createTorusModel(radius * 0.2f, radius, 16, 32);
//    mFillColor = vec4b(206, 169, 49, 255);
//}
//
//void game::act::FlightRing::onUpdate()
//{
//
//}
//
//void game::act::FlightRing::onLeave()
//{
//
//}