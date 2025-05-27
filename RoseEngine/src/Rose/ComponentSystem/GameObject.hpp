#pragma once

#include "Rose/Core/Core.hpp"

namespace Rose {

constexpr size_t ROSE_API MAX_COMPONENTS = 12;
constexpr size_t ROSE_API MAX_OBJECTS = 2000;
using GameObject = int32_t;
using ComponentFlags = std::bitset<MAX_COMPONENTS>;

} // namespace Rose
