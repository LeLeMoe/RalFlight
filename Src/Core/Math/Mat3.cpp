// ----------------------------------------------------------------------------------------------------
// Copyright © 2016-2017 LeLe570929726. All rights reserved.
// 
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator.
//
// @Craete: 2016/12/17 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#include "Mat3.h"

// Core namespace
namespace Core {

	Mat3::Mat3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33) :
		mMatrix{ m11, m12, m13, m21, m22, m23, m31, m32, m33 } {
	}

	Mat3::Mat3(float(&array)[9]) :
		mMatrix{ array[0], array[1], array[2], array[3], array[4], array[5], array[6], array[7], array[8] } {
	}

	Mat3::Mat3(const Mat3 &other) :
		mMatrix{ other.mMatrix[0], other.mMatrix[1], other.mMatrix[2], other.mMatrix[3], other.mMatrix[4], other.mMatrix[5],
			other.mMatrix[6], other.mMatrix[7], other.mMatrix[8] } {
	}

	Mat3 &Mat3::operator=(const Mat3 &other) {
		for (int i = 0; i < 9; ++i) {
			this->mMatrix[i] = other.mMatrix[i];
		}
		return *this;
	}

	Mat3 Mat3::operator+(const Mat3 &matrix) const {
		return Mat3::add(*this, matrix);
	}

	Mat3 &Mat3::operator+=(const Mat3 &matrix) {
		*this = Mat3::add(*this, matrix);
		return *this;
	}

	Mat3 Mat3::operator-(const Mat3 &matrix) const {
		return Mat3::sub(*this, matrix);
	}

	Mat3 &Mat3::operator-=(const Mat3 &matrix) {
		*this = Mat3::sub(*this, matrix);
		return *this;
	}

	Mat3 Mat3::operator*(float scalar) const {
		return Mat3::mul(*this, scalar);
	}

	Mat3 &Mat3::operator*=(float scalar) {
		*this = Mat3::mul(*this, scalar);
		return *this;
	}

	Vec3 Mat3::operator*(const Vec3 &vector) const {
		return Mat3::mul(*this, vector);
	}

	Mat3 Mat3::operator*(const Mat3 &matrix) const {
		return Mat3::mul(*this, matrix);
	}

	Mat3 &Mat3::operator*=(const Mat3 &matrix) {
		*this = Mat3::mul(*this, matrix);
		return *this;
	}

	Mat3 Mat3::operator/(float scalar) const {
		return Mat3::div(*this, scalar);
	}

	Mat3 &Mat3::operator/=(float scalar) {
		*this = Mat3::div(*this, scalar);
		return *this;
	}

	Mat3 &Mat3::add(const Mat3 &matrix) {
		*this = Mat3::add(*this, matrix);
		return *this;
	}

	Mat3 &Mat3::sub(const Mat3 &matrix) {
		*this = Mat3::sub(*this, matrix);
		return *this;
	}

	Mat3 &Mat3::mul(float scalar) {
		*this = Mat3::mul(*this, scalar);
		return *this;
	}

	Vec3 Mat3::mul(const Vec3 &vector) {
		return Mat3::mul(*this, vector);
	}

	Mat3 &Mat3::mul(const Mat3 &matrix) {
		*this = Mat3::mul(*this, matrix);
		return *this;
	}

	Mat3 &Mat3::div(float scalar) {
		*this = Mat3::div(*this, scalar);
		return *this;
	}

	Mat3 &Mat3::transpose() {
		*this = Mat3::transpose(*this);
		return *this;
	}

	inline float Mat3::get(int col, int row) const {
		if (col > 0 && col < 4 && row > 0 && row < 4) {
			return this->mMatrix[(col - 1) + ((row - 1) * 3)];
		} else {
			return 0.0f;
		}
	}

	inline Vec3 Mat3::row(int row) const {
		if (row > 0 && row < 4) {
			return Vec3(this->mMatrix[(row - 1) * 3], this->mMatrix[((row - 1) * 3) + 1], this->mMatrix[((row - 1) * 3) + 2]);
		} else {
			return Vec3(0.0f, 0.0f, 0.0f);
		}
	}

	inline Vec3 Mat3::col(int col) const {
		if (col > 0 && col < 4) {
			return Vec3(this->mMatrix[col - 1], this->mMatrix[col - 1 + 3], this->mMatrix[col - 1 + 6]);
		} else {
			return Vec3(0.0f, 0.0f, 0.0f);
		}
	}

	inline bool Mat3::set(int col, int row, float scalar) {
		if (col > 0 && col < 4 && row > 0 && row < 4) {
			this->mMatrix[(col - 1) + ((row - 1) * 3)] = scalar;
			return true;
		} else {
			return false;
		}
	}

	inline void Mat3::set(float(&array)[9]) {
		for (int i = 0; i < 9; ++i) {
			this->mMatrix[i] = array[i];
		}
	}

	inline bool Mat3::setRow(int row, const Vec3 &vector) {
		if (row > 0 && row < 4) {
			this->mMatrix[(row - 1) * 3] = vector.x();
			this->mMatrix[((row - 1) * 3) + 1] = vector.y();
			this->mMatrix[((row - 1) * 3) + 2] = vector.z();
			return true;
		} else {
			return false;
		}
	}

	inline bool Mat3::setCol(int col, const Vec3 &vector) {
		if (col > 0 && col < 4) {
			this->mMatrix[col - 1] = vector.x();
			this->mMatrix[col - 1 + 3] = vector.y();
			this->mMatrix[col - 1 + 6] = vector.z();
			return true;
		} else {
			return false;
		}
	}

	Mat3 Mat3::add(const Mat3 &matrixA, const Mat3 &matrixB) {
		float tempArray[9] = { 0.0f };
		for (int i = 0; i <= 6; i += 3) {
			__declspec(align(16)) float vectorA[4] = { matrixA.mMatrix[i], matrixA.mMatrix[i + 1], matrixA.mMatrix[i + 2], 0.0f };
			__declspec(align(16)) float vectorB[4] = { matrixB.mMatrix[i], matrixB.mMatrix[i + 1], matrixB.mMatrix[i + 2], 0.0f };
			__declspec(align(16)) float vectorResult[4] = { 0.0f };
			__m128 sseA, sseB, sseResult;
			sseA = _mm_load_ps(vectorA);
			sseB = _mm_load_ps(vectorB);
			sseResult = _mm_add_ps(sseA, sseB);
			_mm_store_ps(vectorResult, sseResult);
			tempArray[i] = vectorResult[0];
			tempArray[i + 1] = vectorResult[1];
			tempArray[i + 2] = vectorResult[2];
		}
		return Mat3(tempArray);
	}

	Mat3 Mat3::sub(const Mat3 &matrixA, const Mat3 &matrixB) {
		float tempArray[9] = { 0.0f };
		for (int i = 0; i <= 6; i += 3) {
			__declspec(align(16)) float vectorA[4] = { matrixA.mMatrix[i], matrixA.mMatrix[i + 1], matrixA.mMatrix[i + 2], 0.0f };
			__declspec(align(16)) float vectorB[4] = { matrixB.mMatrix[i], matrixB.mMatrix[i + 1], matrixB.mMatrix[i + 2], 0.0f };
			__declspec(align(16)) float vectorResult[4] = { 0.0f };
			__m128 sseA, sseB, sseResult;
			sseA = _mm_load_ps(vectorA);
			sseB = _mm_load_ps(vectorB);
			sseResult = _mm_sub_ps(sseA, sseB);
			_mm_store_ps(vectorResult, sseResult);
			tempArray[i] = vectorResult[0];
			tempArray[i + 1] = vectorResult[1];
			tempArray[i + 2] = vectorResult[2];
		}
		return Mat3(tempArray);
	}

	Mat3 Mat3::mul(const Mat3 &matrix, float scalar) {
		float tempArray[9] = { 0.0f };
		for (int i = 0; i <= 6; i += 3) {
			__declspec(align(16)) float vectorA[4] = { matrix.mMatrix[i], matrix.mMatrix[i + 1], matrix.mMatrix[i + 2], 0.0f };
			__declspec(align(16)) float vectorB[4] = { scalar, scalar, scalar, 0.0f };
			__declspec(align(16)) float vectorResult[4] = { 0.0f };
			__m128 sseA, sseB, sseResult;
			sseA = _mm_load_ps(vectorA);
			sseB = _mm_load_ps(vectorB);
			sseResult = _mm_mul_ps(sseA, sseB);
			_mm_store_ps(vectorResult, sseResult);
			tempArray[i] = vectorResult[0];
			tempArray[i + 1] = vectorResult[1];
			tempArray[i + 2] = vectorResult[2];
		}
		return Mat3(tempArray);
	}

	Vec3 Mat3::mul(const Mat3 &matrix, const Vec3 &vector) {
		float tempArray[3] = { 0.0f };
		__declspec(align(16)) float vectorA[4] = { vector.x(), vector.y(), vector.z(), 0.0f };
		__m128 sseA;
		sseA = _mm_load_ps(vectorA);
		for (int i = 0; i <= 6; i += 3) {
			__declspec(align(16)) float vectorB[4] = { matrix.mMatrix[i], matrix.mMatrix[i + 1], matrix.mMatrix[i + 2], 0.0f };
			__declspec(align(16)) float vectorResult[4] = { 0.0f };
			__m128 sseB, sseResult;
			sseB = _mm_load_ps(vectorB);
			sseResult = _mm_mul_ps(sseA, sseB);
			_mm_store_ps(vectorResult, sseResult);
			tempArray[static_cast<int>(i / 3)] = vectorResult[0] + vectorResult[1] + vectorResult[2];
		}
		return Vec3(tempArray);
	}

	Mat3 Mat3::mul(const Mat3 &matrixA, const Mat3 &matrixB) {
		float tempArray[9] = { 0.0f };
		for (int i = 0; i < 9; ++i) {
			__declspec(align(16)) float vectorA[4] = { matrixA.mMatrix[static_cast<int>(i / 3)], matrixA.mMatrix[static_cast<int>(i / 3) + 1],
				matrixA.mMatrix[static_cast<int>(i / 3) + 2], 0.0f };
			__declspec(align(16)) float vectorB[4] = { matrixB.mMatrix[(i % 3)], matrixB.mMatrix[(i % 3) + 3],
				matrixB.mMatrix[(i % 3) + 6], 0.0f };
			__declspec(align(16)) float vectorResult[4] = { 0.0f };
			__m128 sseA, sseB, sseResult;
			sseA = _mm_load_ps(vectorA);
			sseB = _mm_load_ps(vectorB);
			sseResult = _mm_mul_ps(sseA, sseB);
			_mm_store_ps(vectorResult, sseResult);
			tempArray[i] = vectorResult[0] + vectorResult[1] + vectorResult[2];
		}
		return Mat3(tempArray);
	}

	Mat3 Mat3::div(const Mat3 &matrix, float scalar) {
		float tempArray[9] = { 0.0f };
		for (int i = 0; i <= 6; i += 3) {
			__declspec(align(16)) float vectorA[4] = { matrix.mMatrix[i], matrix.mMatrix[i + 1], matrix.mMatrix[i + 2], 0.0f };
			__declspec(align(16)) float vectorB[4] = { scalar, scalar, scalar, 0.0f };
			__declspec(align(16)) float vectorResult[4] = { 0.0f };
			__m128 sseA, sseB, sseResult;
			sseA = _mm_load_ps(vectorA);
			sseB = _mm_load_ps(vectorB);
			sseResult = _mm_div_ps(sseA, sseB);
			_mm_store_ps(vectorResult, sseResult);
			tempArray[i] = vectorResult[0];
			tempArray[i + 1] = vectorResult[1];
			tempArray[i + 2] = vectorResult[2];
		}
		return Mat3(tempArray);
	}

	Mat3 Mat3::transpose(const Mat3 &matrix) {
		Mat3 tempMatrix = matrix;
		float tempScalar;
		tempScalar = tempMatrix.mMatrix[1];
		tempMatrix.mMatrix[1] = tempMatrix.mMatrix[3];
		tempMatrix.mMatrix[3] = tempScalar;
		tempScalar = tempMatrix.mMatrix[2];
		tempMatrix.mMatrix[2] = tempMatrix.mMatrix[6];
		tempMatrix.mMatrix[6] = tempScalar;
		tempScalar = tempMatrix.mMatrix[5];
		tempMatrix.mMatrix[5] = tempMatrix.mMatrix[7];
		tempMatrix.mMatrix[7] = tempScalar;
		return tempMatrix;
	}

}