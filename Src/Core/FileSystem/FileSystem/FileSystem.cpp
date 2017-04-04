// ----------------------------------------------------------------------------------------------------
// Copyright Â© 2016-2017 LeLe570929726. All rights reserved.
// 
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator.
//
// @Craete: 2017/03/30 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#include "FileSystem.h"

FileSystem::FileSystem() :
	mRoot(""), mRootPath(nullptr), mCurrentPath(nullptr) {
}

FileSystem::FileSystem(const String &root) :
	mRoot(""), mRootPath(nullptr), mCurrentPath(nullptr) {
	if (this->checkPathExist(root) == true) {
		this->mRoot = root;
	}
}

FileSystem::FileSystem(const Path &root) :
	mRoot(""), mRootPath(nullptr), mCurrentPath(nullptr) {
	// TODO: Check path
}

FileSystem::~FileSystem() {

}

bool FileSystem::checkPathExist(const String &path) const {
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