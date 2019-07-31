// ----------------------------------------------------------------------------------------------------
// Copyright © 2016 - 2019 LeLe570929726. All rights reserved.
//
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator.
//
// @Create: 2016/12/5 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#pragma once

#include "../Global/Token.h"
#include "Scalar.h"

namespace Core {

class Mat3;

class RF_API Vec3 {
public:
	Vec3(real32 x, real32 y, real32 z);
	explicit Vec3(real32 (&array)[3]);
	Vec3(const Vec3 &other);
	Vec3 &operator=(const Vec3 &other);
	~Vec3() = default;

public:
	inline Vec3 operator+(const Vec3 &vector) const { return Vec3::add(*this, vector); }
	inline Vec3 &operator+=(const Vec3 &vector) {
		*this = Vec3::add(*this, vector);
		return *this;
	}
	inline Vec3 operator-(const Vec3 &vector) const { return Vec3::sub(*this, vector); }
	inline Vec3 &operator-=(const Vec3 &vector) {
		*this = Vec3::sub(*this, vector);
		return *this;
	}
	inline Vec3 operator*(real32 scalar) const { return Vec3::mul(*this, scalar); }
	inline Vec3 &operator*=(real32 scalar) {
		*this = Vec3::mul(*this, scalar);
		return *this;
	}
	inline Vec3 operator/(real32 scalar) const { return Vec3::mul(*this, scalar); }
	inline Vec3 &operator/=(real32 scalar) {
		*this = Vec3::div(*this, scalar);
		return *this;
	}

public:
	Vec3 &add(const Vec3 &vector);
	Vec3 &sub(const Vec3 &vector);
	Vec3 &mul(real32 scalar);
	Vec3 &div(real32 scalar);
	real32 module() const;
	real32 rmodule() const;
	Vec3 &normalize();
	real32 dot(const Vec3 &vector) const;
	Vec3 cross(const Vec3 &vector) const;
	inline real32 angle(const Vec3 &vector) const { return Vec3::angle(*this, vector); }
	inline Vec3 project(const Vec3 &vector) const { return Vec3::project(*this, vector); }

public:
	inline real32 x() const { return Vec3::x(*this); }
	inline real32 y() const { return Vec3::y(*this); }
	inline real32 z() const { return Vec3::z(*this); }
	inline void set(real32 (&array)[3]) { Vec3::set(*this, array); }
	inline void setX(real32 x) { Vec3::setX(*this, x); }
	inline void setY(real32 y) { Vec3::setY(*this, y); }
	inline void setZ(real32 z) { Vec3::setZ(*this, z); }

public:
	inline bool isZero() const { return Vec3::isZero(*this); }
	inline bool isOne() const { return Vec3::isOne(*this); }

public:
	static Vec3 add(const Vec3 &vectorA, const Vec3 &vectorB);
	static Vec3 sub(const Vec3 &vectorA, const Vec3 &vectorB);
	static Vec3 mul(const Vec3 &vector, real32 scalar);
	static Vec3 div(const Vec3 &vector, real32 scalar);
	static real32 module(const Vec3 &vector);
	static real32 rmodule(const Vec3 &vector);
	static Vec3 normalize(const Vec3 &vector);
	static real32 dot(const Vec3 &vectorA, const Vec3 &vectorB);
	static Vec3 cross(const Vec3 &vectorA, const Vec3 &vectorB);
	static real32 angle(const Vec3 &vectorA, const Vec3 &vectorB);
	static Vec3 project(const Vec3 &vectorA, const Vec3 &vectorB);

public:
	static real32 x(const Vec3 &vector);
	static real32 y(const Vec3 &vector);
	static real32 z(const Vec3 &vector);
	static void set(Vec3 &vector, real32 (&array)[3]);
	static void setX(Vec3 &vector, real32 x);
	static void setY(Vec3 &vector, real32 y);
	static void setZ(Vec3 &vector, real32 z);

public:
	static bool isZero(const Vec3 &vector);
	static bool isOne(const Vec3 &vector);

public:
	static const Vec3 zero;

private:
	friend Mat3;

private:
	RF_ALIGN16 real32 mVector[4];
};

} // namespace Core