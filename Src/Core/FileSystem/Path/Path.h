// ----------------------------------------------------------------------------------------------------
// Copyright Â© 2016-2017 LeLe570929726. All rights reserved.
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

public:
	Path &operator/=(const String &path);
	Path &operator/=(const Path &path);
	Path operator/(const String &path) const;
	Path operator/(const Path &path) const;

public:
	bool isExist() const;
	bool isEmpty() const;

public:
	bool create();

public:
	String getPath() const;

public:
	static Path fromLocal(const String &path);

private:
	static PathItem *pathLocalToItem(const String &path);
	static String Path::itemToLocalPath(const PathItem *item);
	static bool checkPathExist(const String &path);
	static PathItem *findBottomItem(PathItem *pathItem);
	static PathItem *createPathItemTree(const String &path);
	static PathItem *copyPathItemTree(PathItem *pathItem);
	static void deletePathItemTree(PathItem *pathItem);

private:
	PathItem *mRootPathItem;
};

#endif				// RALFLIGHT_SRC_CORE_FILESYSTEM_PATH_H