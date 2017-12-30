// ----------------------------------------------------------------------------------------------------
// Copyright © 2016-2017 LeLe570929726. All rights reserved.
// 
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator.
//
// @Craete: 2017/1/17 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#ifndef RALFLIGHT_SRC_CORE_GLOBAL_MACRO_H
#define RALFLIGHT_SRC_CORE_GLOBAL_MACRO_H

// Project name
#define PROJECT_NAME "RalFlight"

// Project version
#define PROJECT_VERSION_MAJOR 0
#define PROJECT_VERSION_MINOR 1

// Project version release
#define PROJECT_VERSION_RELEASE "0.1 Alpha1"

// System token
#define RALFLIGHT_SYSTEM_LINUX

// Build token
#define RALFLIGHT_BUILD

// Export token
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
    #ifdef RALFLIGHT_BUILD
        #define RALFLIGHT_API __declspec(dllexport)
    #else
        #define RALFLIGHT_API __declspec(dllimport)
    #endif
#elif defined(RALFLIGHT_SYSTEM_LINUX)
    #define RALFLIGHT_API __attribute__ ((visibility("default")))
#endif

// Align
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
    #define ALIGN16 __declspec(align(16))
#elif defined(RALFLIGHT_SYSTEM_LINUX)
    #define ALIGN16 __attribute__((aligned(16)))
#endif

#endif          // RALFLIGHT_SRC_CORE_GLOBAL_MACRO_H
