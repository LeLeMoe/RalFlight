// ----------------------------------------------------------------------------------------------------
// Copyright © 2016-2017 LeLe570929726. All rights reserved.
// 
// @Project: RalFlight
// @License: Licensed under GNU General Public License v3.
// @Description: A free and open-source flight simulator.
//
// @Craete: 2016/12/24 by LeLe570929726
// ----------------------------------------------------------------------------------------------------
#include "Scalar.h"

// Core namespace
namespace Core {

	template <>
	float Scalar<float>::cos(float scalar) {
		return std::cosf(scalar);
	}

	template <>
	float Scalar<float>::sin(float scalar) {
		return std::sinf(scalar);
	}

	template <>
	float Scalar<float>::tan(float scalar) {
		return std::tanf(scalar);
	}

	template <>
	float Scalar<float>::acos(float scalar) {
		return std::acosf(scalar);
	}

	template <>
	float Scalar<float>::asin(float scalar) {
		return std::asinf(scalar);
	}

	template <>
	float Scalar<float>::atan(float scalar) {
		return std::atanf(scalar);
	}

	template <>
	float Scalar<float>::pow(float scalarBase, float scalarExp) {
		return std::powf(scalarBase, scalarExp);
	}

	template <>
	float Scalar<float>::sqrt(float scalar) {
		return std::sqrtf(scalar);
	}

	template <>
	float Scalar<float>::log(float scalar) {
		return std::logf(scalar);
	}

	template <>
	double Scalar<double>::cos(double scalar) {
		return std::cos(scalar);
	}

	template <>
	double Scalar<double>::sin(double scalar) {
		return std::sin(scalar);
	}

	template <>
	double Scalar<double>::tan(double scalar) {
		return std::tan(scalar);
	}

	template <>
	double Scalar<double>::acos(double scalar) {
		return std::acos(scalar);
	}

	template <>
	double Scalar<double>::asin(double scalar) {
		return std::asin(scalar);
	}

	template <>
	double Scalar<double>::atan(double scalar) {
		return std::atan(scalar);
	}

	template <>
	double Scalar<double>::pow(double scalarBase, double scalarExp) {
		return std::pow(scalarBase, scalarExp);
	}

	template <>
	double Scalar<double>::sqrt(double scalar) {
		return std::sqrt(scalar);
	}

	template <>
	double Scalar<double>::log(double scalar) {
		return std::log(scalar);
	}

}