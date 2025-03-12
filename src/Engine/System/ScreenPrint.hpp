/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -ScreenPrint.hpp-
 *      Unfinished utility for printing text on screen.
 */

#pragma once
#include "Core/Types/BasicTypes.hpp"
#include "Core/Utils/Vector2.hpp"
#include "Core/Utils/Vector4.hpp"

namespace anim
{
    //Translucent Green
    #define FGCOL_TRGREEN {0x00, 0xFF, 0x00, 0x80}
    //Translucent Leafy Green
    #define FGCOL_TRLEAFY {0x00, 0xFF, 0xA5, 0x80}
    //Opaque Green
    #define FGCOL_OPGREEN {0x00, 0xFF, 0x00, 0xFF}
    //Opaque Leafy Green
    #define FGCOL_OPLEAFY {0x00, 0xFF, 0xA5, 0xFF}

    #define PRINT_BUFFER_SIZE 1024

    void screenPrintf(const vec2u& position, u32 fontSize, const char* format, ...);

    void screenPrintf(const vec2u& position,
                      u32 fontSize, vec4b color, const char* format, ...);

    extern char screenPrintBuffer[1024];
}