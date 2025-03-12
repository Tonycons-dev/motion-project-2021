/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -ioConstants.hpp-
 *      Input-Output related constants.
 */

#pragma once

namespace anim::io
{

constexpr auto DEVICE_TIMEOUT_DELAY = 33L;
constexpr auto DEVICE_UPDATE_DELAY  = 33L;
constexpr auto DEVICE_MESSAGE_BEGIN = '$';
constexpr auto DEVICE_MESSAGE_END   = '~';

#define SHADER_PATH(file) "res/shaders/" file
#define IMAGE_PATH(file) "res/images/" file
}