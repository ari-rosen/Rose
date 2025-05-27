#pragma once

#include "pch.hpp"

#ifdef ROSE_PLATFORM_MACOS
    #ifdef ROSE_BUILD_DYLIB
        #define ROSE_API __attribute__((visibility("default")))
    #else
        #define ROSE_API
    #endif
#endif

#define BIT(x) (1 << x)
#define ROSE_BIND_EVENT_FUNC(func) (std::bind(&func, this, std::placeholders::_1))

