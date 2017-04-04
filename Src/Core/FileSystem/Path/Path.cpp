// ----------------------------------------------------------------------------------------------------
// Copyright © 2016-2017 LeLe570929726. All rights reserved.
// 
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator.
//
// @Craete: 2017/04/01 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#include "Path.h"

Path::Path() :
	mRootPathItem(nullptr), mParent(nullptr) {
}

Path::Path(const String &path) :
	mRootPathItem(nullptr), mParent(nullptr) {
}

Path::Path(const Path &other) :
	mRootPathItem(nullptr), mParent(nullptr) {
}

Path &Path::operator=(const Path &other) {
	this->mRootPathItem = nullptr;
	this->mParent = nullptr;
	return *this;
}

Path::~Path() {

}

PathItem *Path::pathLocalToIteam(const String &path) const {
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
	PathItem *rootPath = new PathItem;
	PathItem *currentPath = rootPath;
	for (auto iterator = path.begin(); iterator != path.end(); ++iterator) {
		if (*iterator != L'/') {
			currentPath->mName += *iterator;
		} else {
			currentPath->mChild = new PathItem;
			currentPath->mChild->mParent = currentPath;
			currentPath = currentPath->mChild;
		}
	}
#endif
}

bool Path::checkPathExist(const String &path) const {
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
	DWORD result = GetFileAttributesW(path.toUtf16().c_str());
	if (result == FILE_ATTRIBUTE_DIRECTORY) {
		return true;
	}
	else {
		return false;
	}
#endif
}