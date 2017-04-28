// ----------------------------------------------------------------------------------------------------
// Copyright © 2016-2017 LeLe570929726. All rights reserved.
// 
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator.
//
// @Craete: 2016/12/13 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#ifndef RALFLIGHT_SRC_CORE_MATH_MAT2_H
#define RALFLIGHT_SRC_CORE_MATH_MAT2_H

#include "../../Global/Macro/Macro.h"
#include "../Vec2/Vec2.h"
#include <intrin.h>

// Core namespace
namespace Core {

	class RALFLIGHT_API Mat2 {
	public:
		Mat2(float m11, float m12, float m21, float m22);
		Mat2(float(&array)[4]);
		Mat2(const Mat2 &other);
		Mat2 &operator=(const Mat2 &other);
		~Mat2() = default;

	public:
		Mat2 operator+(const Mat2 &matrix) const;
		Mat2 &operator+=(const Mat2 &matrix);
		Mat2 operator-(const Mat2 &matrix) const;
		Mat2 &operator-=(const Mat2 &matrix);
		Mat2 operator*(float scalar) const;
		Mat2 &operator*=(float scalar);
		Vec2 operator*(const Vec2 &vector) const;
		Mat2 operator*(const Mat2 &matrix) const;
		Mat2 &operator*=(const Mat2 &matrix);
		Mat2 operator/(float scalar) const;
		Mat2 &operator/=(float scalar);

	public:
		Mat2 &tra();		// Transpose

	public:
		float get(int col, int row) const;
		Vec2 row(int row) const;
		Vec2 col(int col) const;

	public:
		bool set(int col, int row, float scalar);
		void set(float(&array)[4]);
		bool setRow(int row, const Vec2 &vector);
		bool setCol(int col, const Vec2 &vector);

	private:
		float mMatrix[4];
	};

}

#endif		// RALFLIGHT_SRC_CORE_MATH_MAT2_H
