// ----------------------------------------------------------------------------------------------------
// Copyright © 2016 - 2019 LeLe570929726. All rights reserved.
//
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator which is based on Qt.
//
// @Create: 2019/09/20 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#pragma once

#include "../Global/Token.h"

namespace Core {

template <typename T>
using DefaultPointerDeleter = decltype([](T *pointer) { delete pointer; });

template <typename T>
using DefaultArrayPointerDeleter = decltype([](T *pointer) { delete[] pointer; });

template <typename T, typename Deleter = DefaultPointerDeleter<T>>
class RF_API_TEMPLATE UniquePointer {
public:
	UniquePointer() : mPointer(nullptr), mDeleter(Deleter()) {}
	UniquePointer(T *pointer) : mPointer(pointer), mDeleter(Deleter()) {}
	UniquePointer(T *pointer, const Deleter &deleter) : mPointer(pointer), mDeleter(deleter) {}
	UniquePointer(const UniquePointer &other) = delete;
	UniquePointer(UniquePointer &&other) noexcept {
		this->mPointer = other.mPointer;
		this->mDeleter = other.mDeleter;
		other.mPointer = nullptr;
	}
	UniquePointer &operator=(const UniquePointer &other) = delete;
	UniquePointer &operator=(UniquePointer &&other) noexcept {
		this->mPointer = other.mPointer;
		this->mDeleter = other.mDeleter;
		other.mPointer = nullptr;
	}
	~UniquePointer() {
		if (this->mPointer != nullptr) {
			this->mDeleter(this->mPointer);
		}
	}

public:
	T *release() {
		auto tmpPtr = this->mPointer;
		this->mPointer = nullptr;
		return tmpPtr;
	}

private:
	T *mPointer;
	Deleter mDeleter;
};

template <typename T, typename Deleter>
class RF_API_TEMPLATE UniquePointer<T[], Deleter> {};

} // namespace Core
