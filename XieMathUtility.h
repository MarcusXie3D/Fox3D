#pragma once
#include "XieVector.h"
#include "XieVertex.h"
#include "XieMatrix.h"

namespace XieMathUtility {
	float lerp(const float &v1, const float &v2, const float &coe);

	XieVector lerp(const XieVector &v1, const XieVector &v2, const float &coe);

	XieColor lerp(const XieColor &v1, const XieColor &v2, const float &coe);

	XieVertex lerp(const XieVertex &v1, const XieVertex &v2, const float &coe);

	float max(float a, float b);

	XieMatrix scale(const float &x, const float &y, const float &z);

	float dot(const XieVector &v1, const XieVector &v2);

	XieVector cross(const XieVector &v1, const XieVector &v2);

	XieMatrix transpose(const XieMatrix& mat);

	float determinant(const XieMatrix& mat);

	float adjElem(
		const float &a1, const float &a2, const float &a3,
		const float &b1, const float &b2, const float &b3,
		const float &c1, const float &c2, const float &c3);

	XieMatrix adjoint(const XieMatrix& mat);

	XieMatrix inverse(const XieMatrix &mat);

	//phi needs to be an angle in radians
	XieMatrix rotate(const float &x, const float &y, const float &z, const float &phi);

	XieMatrix translate(const float &x, const float &y, const float &z);

	XieMatrix view(const XieVector &eye, const XieVector &lookAt, const XieVector &up);

	//fov needs to be an angle in radians
	XieMatrix project(const float &fov, const float &aspect, const float &near, const float &far);
}
