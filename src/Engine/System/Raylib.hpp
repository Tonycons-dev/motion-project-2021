/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -Raylib.hpp-
 *   Wrapper for the C source raylib header file.
 */

#ifndef _RAYLIB_INCLUDE_
#define _RAYLIB_INCLUDE_

extern "C" {
#include <raylib.h>
}

#include <Core/Utils/Vector2.hpp>
#include <Core/Utils/Vector3.hpp>
#include <Core/Utils/Vector4.hpp>

using RlVector2        = Vector2;
using RlVector3        = Vector3;
using RlVector4        = Vector4;
using RlQuaternion     = Quaternion;
using RlMatrix         = Matrix;
using RlColor          = Color;
using RlRectangle      = Rectangle;
using RlImage          = Image;
using RlRenderTexture  = RenderTexture;
using RlNPatchInfo     = NPatchInfo;
using RlCharInfo       = CharInfo;
using RlFont           = Font;
using RlCamera         = Camera;
using RlCamera2D       = Camera2D;
using RlMesh           = Mesh;
using RlShader         = Shader;
using RlMaterialMap    = MaterialMap;
using RlMaterial       = Material;
using RlModel          = Model;
using RlTransform      = Transform;
using RlBoneInfo       = BoneInfo;
using RlModelAnimation = ModelAnimation;
using RlRay            = Ray;
using RlRayHitInfo     = RayHitInfo;
using RlBoundingBox    = BoundingBox;
using RlWave           = Wave;
using RlSound          = Sound;
using RlMusic          = Music;
using RlAudioStream    = AudioStream;
using RlVrDeviceInfo   = VrDeviceInfo;

#endif