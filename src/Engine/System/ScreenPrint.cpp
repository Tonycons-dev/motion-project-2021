/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -ScreenPrint.cpp-
 *      Unfinished utility for printing text on screen.
 */

#include "Engine/System/ScreenPrint.hpp"
#include "Engine/System/Raylib.hpp"

char anim::screenPrintBuffer[PRINT_BUFFER_SIZE];


void anim::screenPrintf(const vec2u& position, u32 fontSize, const char* format, ...)
{
    std::memset(screenPrintBuffer, '\0', sizeof(char) * PRINT_BUFFER_SIZE);

    va_list args;
    va_start(args, format);
#ifdef _WIN32
    vsprintf_s(screenPrintBuffer, format, args);
#else
    vsprintf(screenPrintBuffer, format, args);
#endif
    va_end(args);
    DrawText(screenPrintBuffer,
             int(position.x), int(position.y), int(fontSize), GREEN);
}

void anim::screenPrintf(const vec2u &position,
                        u32 fontSize, vec4b color, const char *format, ...)
{
    std::memset(screenPrintBuffer, '\0', sizeof(char) * PRINT_BUFFER_SIZE);

    va_list args;
    va_start(args, format);
#ifdef _WIN32
    vsprintf_s(screenPrintBuffer, format, args);
#else
    vsprintf(screenPrintBuffer, format, args);
#endif
    va_end(args);

    DrawText(screenPrintBuffer, int(position.x), int(position.y),
             int(fontSize), *reinterpret_cast<Color*>(&color));
}