/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -gfxConsants.hpp-
 *      Graphics-related constants.
 */

#pragma once

#ifdef PLATFORM_DESKTOP
#define GFX_GLSL_VERSION 330
#else
#define GFX_GLSL_VERSION 100
#endif