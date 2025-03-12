#ifndef _ANIM_RT_CONSTANTS_
#define _ANIM_RT_CONSTANTS_

#include "vector3.hpp"
#include "vector2.hpp"


typedef unsigned char  u8;
typedef signed   char  s8;
typedef unsigned short u16;
typedef signed   short s16;
typedef unsigned int   u32;
typedef signed   int   s32;
typedef unsigned long  u64;
typedef signed   long  s64;
typedef float          f32;

using Vector2f = Vector2<f32>;
using Vector2i = Vector2<s32>;
using Vector2u = Vector2<u32>;
using Vector3f = Vector3<f32>;
using Vector3i = Vector3<s32>;
using Vector3u = Vector3<u32>;


#define BUTTON_ACCEPT 0
#define BUTTON_SELECT 2
#define BUTTON_START  1
#define TRANSMIT_PIN  22
#define RECEIVE_PIN   23
#define UPDATE_SPEED  33
#define DEFAULT_BAUD  9600
#define MESSAGE_BEGIN '$'
#define MESSAGE_OVER  '~'
#define PACKET_SIZE   17


extern Vector3f minDeadzones;
extern Vector3f maxDeadzones;

extern u8 buttonLayout[3];
extern u8 buttonStates[3];

#endif