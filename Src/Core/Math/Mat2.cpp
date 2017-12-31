// ----------------------------------------------------------------------------------------------------
// Copyright © 2016 - 2018 LeLe570929726. All rights reserved.
// 
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator.
//
// @Craete: 2016/12/16 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#include "Mat2.h"

// Core namespace
namespace Core {

	const Mat2 Mat2::zero(0.0f, 0.0f, 0.0f, 0.0f);
	const Mat2 Mat2::identity(1.0f, 0.0f, 0.0f, 1.0f);

	Mat2::Mat2(float m11, float m12, float m21, float m22) :
		mMatrix{ m11, m12, m21, m22 } {
	}

	Mat2::Mat2(float(&array)[4]) :
		mMatrix{ array[0], array[1], array[2], array[3] } {
	}

	Mat2::Mat2(const Mat2 &other) :
		mMatrix{ other.mMatrix[0], other.mMatrix[1], other.mMatrix[2], other.mMatrix[3] } {
	}

	Mat2 &Mat2::operator=(const Mat2 &other) {
		this->mMatrix[0] = other.mMatrix[0];
		this->mMatrix[1] = other.mMatrix[1];
		this->mMatrix[2] = other.mMatrix[2];
		this->mMatrix[3] = other.mMatrix[3];
		return *this;
	}

	Mat2 Mat2::add(const Mat2 &matrixA, const Mat2 &matrixB) {
		ALIGN16 float vectorAA[4] = { matrixA.mMatrix[0], matrixA.mMatrix[1], matrixA.mMatrix[2], matrixA.mMatrix[3] };
		ALIGN16 float vectorAB[4] = { matrixB.mMatrix[0], matrixB.mMatrix[1], matrixB.mMatrix[2], matrixB.mMatrix[3] };
		ALIGN16 float vectorAResult[4] = { 0.0f };
		__m128 sseA, sseB, sseResult;
		sseA = _mm_load_ps(vectorAA);
		sseB = _mm_load_ps(vectorAB);
		sseResult = _mm_add_ps(sseA, sseB);
		_mm_store_ps(vectorAResult, sseResult);
		return Mat2(vectorAResult[0], vectorAResult[1], vectorAResult[2], vectorAResult[3]);
	}

	Mat2 Mat2::sub(const Mat2 &matrixA, const Mat2 &matrixB) {
		ALIGN16 float vectorAA[4] = { matrixA.mMatrix[0], matrixA.mMatrix[1], matrixA.mMatrix[2], matrixA.mMatrix[3] };
		ALIGN16 float vectorAB[4] = { matrixB.mMatrix[0], matrixB.mMatrix[1], matrixB.mMatrix[2], matrixB.mMatrix[3] };
		ALIGN16 float vectorAResult[4] = { 0.0f };
		__m128 sseA, sseB, sseResult;
		sseA = _mm_load_ps(vectorAA);
		sseB = _mm_load_ps(vectorAB);
		sseResult = _mm_sub_ps(sseA, sseB);
		_mm_store_ps(vectorAResult, sseResult);
		return Mat2(vectorAResult[0], vectorAResult[1], vectorAResult[2], vectorAResult[3]);
	}

	Mat2 Mat2::mul(const Mat2 &matrix, float scalar) {
		ALIGN16 float vectorA[4] = { matrix.mMatrix[0], matrix.mMatrix[1], matrix.mMatrix[2], matrix.mMatrix[3] };
		ALIGN16 float vectorB[4] = { scalar, scalar, scalar, scalar };
		ALIGN16 float vectorResult[4] = { 0.0f };
		__m128 sseA, sseB, sseResult;
		sseA = _mm_load_ps(vectorA);
		sseB = _mm_load_ps(vectorB);
		sseResult = _mm_mul_ps(sseA, sseB);
		_mm_store_ps(vectorResult, sseResult);
		return Mat2(vectorResult[0], vectorResult[1], vectorResult[2], vectorResult[3]);
	}

	Vec2 Mat2::mul(const Mat2 &matrix, const Vec2 &vector) {
		ALIGN16 float vectorA[4] = { matrix.mMatrix[0], matrix.mMatrix[1], matrix.mMatrix[2], matrix.mMatrix[3] };
		ALIGN16 float vectorB[4] = { vector.getX(), vector.getY(), vector.getX(), vector.getY() };
		ALIGN16 float vectorResult[4] = { 0.0f };
		__m128 sseA, sseB, sseResult;
		sseA = _mm_load_ps(vectorA);
		sseB = _mm_load_ps(vectorB);
		sseResult = _mm_mul_ps(sseA, sseB);
		_mm_store_ps(vectorResult, sseResult);
		return Vec2(vectorResult[0] + vectorResult[1], vectorResult[2] + vectorResult[3]);
	}

	Mat2 Mat2::mul(const Mat2 &matrixA, const Mat2 &matrixB) {
		ALIGN16 float vectorAA[4] = { matrixA.mMatrix[0], matrixA.mMatrix[1], matrixA.mMatrix[0], matrixA.mMatrix[1] };
		ALIGN16 float vectorAB[4] = { matrixB.mMatrix[0], matrixB.mMatrix[2], matrixB.mMatrix[1], matrixB.mMatrix[3] };
		ALIGN16 float vectorAC[4] = { matrixA.mMatrix[2], matrixA.mMatrix[3], matrixA.mMatrix[2], matrixA.mMatrix[3] };
		ALIGN16 float vectorAD[4] = { matrixB.mMatrix[0], matrixB.mMatrix[2], matrixB.mMatrix[1], matrixB.mMatrix[3] };
		ALIGN16 float vectorAResultA[4] = { 0.0f };
		ALIGN16 float vectorAResultB[4] = { 0.0f };
		__m128 sseA, sseB, sseC, sseD, sseResultA, sseResultB;
		sseA = _mm_load_ps(vectorAA);
		sseB = _mm_load_ps(vectorAB);
		sseC = _mm_load_ps(vectorAC);
		sseD = _mm_load_ps(vectorAD);
		sseResultA = _mm_mul_ps(sseA, sseB);
		sseResultB = _mm_mul_ps(sseC, sseD);
		_mm_store_ps(vectorAResultA, sseResultA);
		_mm_store_ps(vectorAResultB, sseResultB);

		return Mat2(vectorAResultA[0] + vectorAResultA[1], vectorAResultA[2] + vectorAResultA[3], 
					vectorAResultB[0] + vectorAResultB[1], vectorAResultB[2] + vectorAResultB[3]);
	}

	Mat2 Mat2::div(const Mat2 &matrix, float scalar) {
		assert(scalar);
		ALIGN16 float vectorA[4] = { matrix.mMatrix[0], matrix.mMatrix[1], matrix.mMatrix[2], matrix.mMatrix[3] };
		ALIGN16 float vectorB[4] = { scalar, scalar, scalar, scalar };
		ALIGN16 float vectorResult[4] = { 0.0f };
		__m128 sseA, sseB, sseResult;
		sseA = _mm_load_ps(vectorA);
		sseB = _mm_load_ps(vectorB);
		sseResult = _mm_div_ps(sseA, sseB);
		_mm_store_ps(vectorResult, sseResult);
		return Mat2(vectorResult[0], vectorResult[1], vectorResult[2], vectorResult[3]);
	}

	Mat2 Mat2::transpose(const Mat2 &matrix) {
		Mat2 tempMatrix = matrix;
		float tempScalar = tempMatrix.mMatrix[1];
		tempMatrix.mMatrix[1] = tempMatrix.mMatrix[2];
		tempMatrix.mMatrix[2] = tempScalar;
		return tempMatrix;
	}

	float Mat2::determinant(const Mat2 &matrix) {
		ALIGN16 float vectorA[4] = { matrix.mMatrix[0], matrix.mMatrix[1], 0, 0 };
		ALIGN16 float vectorB[4] = { matrix.mMatrix[3], matrix.mMatrix[2], 0, 0 };
		ALIGN16 float vectorResult[4] = { 0.0f };
		__m128 sseA, sseB, sseResult;
		sseA = _mm_load_ps(vectorA);
		sseB = _mm_load_ps(vectorB);
		sseResult = _mm_mul_ps(sseA, sseB);
		_mm_store_ps(vectorResult, sseResult);
		return vectorResult[0] - vectorResult[1];
	}

	float Mat2::get(const Mat2 &matrix, int col, int row) {
		assert(col > 0 && col < 3);
		assert(row > 0 && row < 3);
		return matrix.mMatrix[(col - 1) + (2 * (row - 1))];
	}

	Vec2 Mat2::getRow(const Mat2 &matrix, int row) {
		assert(row > 0 && row < 3);
		return Vec2(matrix.mMatrix[(row - 1) << 1], matrix.mMatrix[((row - 1) << 1) + 1]);
	}

	Vec2 Mat2::getCol(const Mat2 &matrix, int col) {
		assert(col > 0 && col < 3);
		return Vec2(matrix.mMatrix[col - 1], matrix.mMatrix[col - 1 + 2]);
	}

	void Mat2::set(Mat2 &matrix, int col, int row, float scalar) {
		assert(col > 0 && col < 3);
		assert(row > 0 && row < 3);
		matrix.mMatrix[(col - 1) + (2 * (row - 1))] = scalar;
	}

	void Mat2::set(Mat2 &matrix, float(&array)[4]) {
		matrix = Mat2(array);
	}

	void Mat2::setRow(Mat2 &matrix, int row, const Vec2 &vector) {
		assert(row > 0 && row < 3);
		matrix.mMatrix[(row - 1) << 1] = vector.getX();
		matrix.mMatrix[((row - 1) << 1) + 1] = vector.getY();
	}

	void Mat2::setCol(Mat2 &matrix, int col, const Vec2 &vector) {
		assert(col > 0 && col < 3);
		matrix.mMatrix[col - 1] = vector.getX();
		matrix.mMatrix[col - 1 + 2] = vector.getY();
	}

}