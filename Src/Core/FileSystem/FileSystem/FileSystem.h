// ----------------------------------------------------------------------------------------------------
// Copyright © 2016-2017 LeLe570929726. All rights reserved.
// 
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator.
//
// @Craete: 2017/03/28 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#ifndef RALFLIGHT_SRC_CORE_FILESYSTEM_FILESYSTEM_H
#define RALFLIGHT_SRC_CORE_FILESYSTEM_FILESYSTEM_H

#include "../../Global/Macro/Macro.h"
#include "../Path/Path.h"
#include "../../STD/String/String.h"
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
	#include<Windows.h> 
#endif

class RALFLIGHT_API FileSystem {
public:
	FileSystem();
	FileSystem(const String &root);
	FileSystem(const Path &root);
	FileSystem(const FileSystem &other) = delete;
	FileSystem &operator=(const FileSystem &other) = delete;
	~FileSystem();

public:
	Path &operator/(const String &path);

public:
	String getRoot() const;
	String getAbsolutePath() const;
	String getRelativePath() const;

private:
	bool checkPathExist(const String &path) const;

private:
	String mRoot;
	Path *mRootPath;
	Path *mCurrentPath;
};

#endif 			// RALFLIGHT_SRC_CORE_FILESYSTEM_FILESYSTEM_H