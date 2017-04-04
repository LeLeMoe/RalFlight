// ----------------------------------------------------------------------------------------------------
// Copyright © 2016-2017 LeLe570929726. All rights reserved.
// 
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator.
//
// @Craete: 2017/04/01 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#ifndef RALFLIGHT_SRC_CORE_FILESYSTEM_PATH_H
#define RALFLIGHT_SRC_CORE_FILESYSTEM_PATH_H

#include "../../Global/Macro/Macro.h"
#include "../../STD/String/String.h"
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
	#include<Windows.h> 
#endif

struct PathItem {
	PathItem *mParent;
	String mName;
	PathItem *mChild;
};

class RALFLIGHT_API Path {
public:
	Path();
	Path(const String &path);
	Path(const Path &other);
	Path &operator=(const Path &other);
	~Path();

private:
	PathItem *pathLocalToIteam(const String &path) const;
	bool checkPathExist(const String &path) const;

private:
	PathItem *mRootPathItem;
	Path *mParent;
};

#endif				// RALFLIGHT_SRC_CORE_FILESYSTEM_PATH_H