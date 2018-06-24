// ----------------------------------------------------------------------------------------------------
// Copyright © 2016 - 2018 LeLe570929726. All rights reserved.
// 
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator which is based on Qt.
//
// @Create: 2018/5/5 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#pragma once

#include <QtGlobal>

// System token
#if defined(Q_OS_LINUX)
    #define RF_OS_LINUX
#elif defined(Q_OS_WIN)
    #define RF_OS_WIN
#elif defined(Q_OS_MACOS)
    #define RF_OS_MACOS
#endif

// Build token
#undef RF_API
#if defined(RF_SOUNDPAL_BUILD)
    #define RF_API Q_DECL_EXPORT
#else
    #define RF_API Q_DECL_IMPORT
#endif

// Template class token
#undef RF_API_TEMPLATE
#define RF_API_TEMPLATE