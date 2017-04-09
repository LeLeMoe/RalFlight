// ----------------------------------------------------------------------------------------------------
// Copyright Â© 2016-2017 LeLe570929726. All rights reserved.
// 
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator.
//
// @Craete: 2017/04/01 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#include "Path.h"

Path::Path() :
	mRootPathItem(nullptr) {
}

Path::Path(const String &path) :
	mRootPathItem(Path::createPathItemTree(path)) {
}

Path::Path(const Path &other) :
	mRootPathItem(Path::copyPathItemTree(other.mRootPathItem)) {
}

Path &Path::operator=(const Path &other) {
	this->mRootPathItem = Path::copyPathItemTree(other.mRootPathItem);
	return *this;
}

Path::~Path() {
	Path::deletePathItemTree(this->mRootPathItem);
}

Path &Path::operator/=(const String &path) {
	if (this->mRootPathItem != nullptr) {
		PathItem *currentItem = Path::findBottomItem(this->mRootPathItem->mChild);
		currentItem->mChild = new PathItem{ 0 };
		currentItem->mChild->mName = path;
	}
	else {
		this->mRootPathItem = new PathItem{ 0 };
		this->mRootPathItem->mName = path;
	}
	return *this;
}

Path &Path::operator/=(const Path &path) {
	Path::findBottomItem(this->mRootPathItem)->mChild = Path::copyPathItemTree(path.mRootPathItem);
	return *this;
}

Path Path::operator/(const String &path) const {
	Path tempPath;
	tempPath.mRootPathItem = Path::pathLocalToItem(path);
	Path::findBottomItem(tempPath.mRootPathItem)->mChild = Path::pathLocalToItem(path);
	return tempPath;
}

Path Path::operator/(const Path &path) const {
	Path tempPath;
	tempPath.mRootPathItem = Path::copyPathItemTree(path.mRootPathItem);
	Path::findBottomItem(tempPath.mRootPathItem)->mChild = Path::copyPathItemTree(path.mRootPathItem);
	return tempPath;
}

bool Path::isExist() const {
	return Path::checkPathExist(Path::itemToLocalPath(this->mRootPathItem));
}

bool Path::isEmpty() const {
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
	if (this->isExist() == false) {
		return true;
	} else {
		String tempPath = Path::itemToLocalPath(this->mRootPathItem) + '*';
		WIN32_FIND_DATAW findInfo;
		HANDLE tempHandle = FindFirstFileW(tempPath.toUtf16().c_str(), &findInfo);
		if (tempHandle == INVALID_HANDLE_VALUE) {
			return true;
		} else {
			do {
				if (findInfo.cFileName[0] == L'.') {
					if (findInfo.cFileName[1] != L'.' && findInfo.cFileName[1] != 0) {
						FindClose(tempHandle);
						return false;
					}
				} else {
					FindClose(tempHandle);
					return false;
				}
			} while (FindNextFileW(tempHandle, &findInfo) == TRUE);
			FindClose(tempHandle);
			return true;
		}
	}
#endif
}

String Path::getPath() const {
	return Path::itemToLocalPath(this->mRootPathItem);
}

Path Path::fromLocal(const String &path) {
	Path tempPath;
	tempPath.mRootPathItem = Path::pathLocalToItem(path);
	return tempPath;
}

bool Path::create() {
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
	String tempPath = Path::itemToLocalPath(this->mRootPathItem);
	if (Path::checkPathExist(tempPath) == true) {
		return true;
	} else {
		if (CreateDirectoryW(tempPath.toUtf16().c_str(), nullptr) == TRUE) {
			return true;
		} else {
			return false;
		}
	}
#endif
}

PathItem *Path::pathLocalToItem(const String &path) {
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
	PathItem *rootPath = new PathItem{ 0 };
	PathItem *currentPath = rootPath;
	for (auto iterator = path.begin(); iterator != path.end(); ++iterator) {
		if (*iterator == '\0') {
			continue;
		} else if (*iterator != '\\') {
			currentPath->mName += *iterator;
		} else if (currentPath->mName.isEmpty() == false) {
			currentPath->mChild = new PathItem{ 0 };
			currentPath->mChild->mParent = currentPath;
			currentPath = currentPath->mChild;
		}
	}
	rootPath->mName = rootPath->mName[0];
	return rootPath;
#endif
}

String Path::itemToLocalPath(const PathItem *item) {
	if (item == nullptr) {
		return "";
	}
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
	String tempPath = item->mName + ":\\";
	PathItem *currentItem = item->mChild;
	while (currentItem != nullptr) {
		tempPath = tempPath + currentItem->mName + '\\';
		currentItem = currentItem->mChild;
	}
	return tempPath;
#endif
}

bool Path::checkPathExist(const String &path) {
#if defined(RALFLIGHT_SYSTEM_WINDOWS)
	DWORD result = GetFileAttributesW(path.toUtf16().c_str());
	if (result == FILE_ATTRIBUTE_DIRECTORY) {
		return true;
	} else {
		return false;
	}
#endif
}

PathItem *Path::findBottomItem(PathItem *pathItem) {
	while (pathItem != nullptr) {
		pathItem = pathItem->mChild;
	}
	return pathItem;
}

PathItem *Path::createPathItemTree(const String &path) {
	PathItem *rootPath = new PathItem{ 0 };
	PathItem *currentPath = rootPath;
	for (auto iterator = path.begin(); iterator != path.end(); ++iterator) {
		if (*iterator == '\0') {
			continue;
		} else if (*iterator != '/') {
			currentPath->mName += *iterator;
		} else if (currentPath->mName.isEmpty() == false) {
			currentPath->mChild = new PathItem{ 0 };
			currentPath->mChild->mParent = currentPath;
			currentPath = currentPath->mChild;
		}
	}
	return rootPath;
}

PathItem *Path::copyPathItemTree(PathItem *pathItem) {
	if (pathItem == nullptr) {
		return nullptr;
	}
	PathItem *rootPath = new PathItem{ 0 };
	PathItem *currentPath = rootPath;
	PathItem *sourceCurrentPath = pathItem;
	while (sourceCurrentPath != nullptr) {
		currentPath->mName = sourceCurrentPath->mName;
		currentPath->mChild = new PathItem{ 0 };
		currentPath = currentPath->mChild;
		sourceCurrentPath = sourceCurrentPath->mChild;
	}
	return rootPath;
}

void Path::deletePathItemTree(PathItem *pathItem) {
	if (pathItem == nullptr) {
		return;
	}
	while (pathItem != nullptr) {
		PathItem *childItem = pathItem->mChild;
		delete pathItem;
		pathItem = childItem;
	}
}