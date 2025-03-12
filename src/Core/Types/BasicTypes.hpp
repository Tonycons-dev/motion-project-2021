#ifndef _CORE_TYPES_
#define _CORE_TYPES_

#include <algorithm>
#include <vector>
#include <array>
#include <atomic>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <sstream>
#include <iterator>
#include <ctime>
#include <cmath>
#include <cstring>
#include <memory>
#include "Core/Types/NumberTypes.hpp"
#include "Core/Utils/Vector2.hpp"
#include "Core/Utils/Vector3.hpp"
#include "Core/Utils/Vector4.hpp"

using word  = uintptr_t;

#define LOG_FAILURE(a) std::cout << "[ANIM] " << a << "\n"
#define LOG_MESSAGE(a) std::cout << "[ANIM] " << a << "\n"

#define CHECK_ALIGNMENT_2BYTE(T) \
static_assert(!(sizeof(T) % 0x02), ##T" is not 2-byte aligned.");

#define CHECK_ALIGNMENT_4BYTE(T) \
static_assert(!(sizeof(T) % 0x04), ##T" is not 4-byte aligned.");

#define CHECK_ALIGNMENT_8BYTE(T) \
static_assert(!(sizeof(T) % 0x08), ##T" is not 8-byte aligned.");

#define CHECK_ALIGNMENT_16BYTE(T) \
static_assert(!(sizeof(T) % 0x10), ##T" is not 16-byte aligned.");

#define CHECK_ALIGNMENT_24BYTE(T) \
static_assert(!(sizeof(T) % 0x18), ##T" is not 24-byte aligned.");

#define CHECK_ALIGNMENT_32BYTE(T) \
static_assert(!(sizeof(T) % 0x20), ##T" is not 32-byte aligned.");

#endif