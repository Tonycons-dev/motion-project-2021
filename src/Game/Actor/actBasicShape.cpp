///* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
// *
// * -actBasicShape.cpp-
// *      Primitive 3D shape for debugging purposes.
// */
//
//#include "Game/Actor/actBasicShape.hpp"
//
//
//BasicShape::BasicShape(s16 preset, vec3f position, vec3f rotation, vec3f size, bool wires)
//    :
//    ActorModel(position, rotation, 1.0f, wires),
//    mSize(size)
//{
//    switch (preset)
//    {
//    case Preset::RECTANGLE: {
//        mModel = LoadModelFromMesh(GenMeshCube(size.x, size.y, size.y));
//        break;
//    }
//    case Preset::SPHERE: {
//        mModel = LoadModelFromMesh(GenMeshSphere(size.x, 32, 32));
//        break;
//    }
//    case Preset::CYLINDER: {
//        mModel = LoadModelFromMesh(GenMeshCylinder(size.x, size.y, 32));
//        break;
//    }
//    case Preset::PYRAMID: {
//        mModel = LoadModelFromMesh(GenMeshCylinder(size.x, size.y, 4));
//        break;
//    }
//    default: {
//        mModel = LoadModelFromMesh(GenMeshCube(size.x, size.y, size.y));
//        break;
//    }
//    }
//}