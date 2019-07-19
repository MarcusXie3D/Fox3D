#pragma once
#include "XieVector.h"
#include "XieVertex.h"
#include "XieMatrix.h"

namespace XieMathUtility {
	float lerp(const float &v1, const float &v2, const float &coe);

	XieVector lerp(const XieVector &v1, const XieVector &v2, const float &coe);

	XieColor lerp(const XieColor &v1, const XieColor &v2, const float &coe);

	XieVertex lerp(const XieVertex &v1, const XieVertex &v2, const float &coe);

	XieMatrix scale(const float &x, const float &y, const float &z);

	float dot(const XieVector &v1, const XieVector &v2);

	XieVector cross(const XieVector &v1, const XieVector &v2);

	//phi needs to be an angle in radians
	XieMatrix rotate(const float &x, const float &y, const float &z, const float &phi);

	XieMatrix translate(const float &x, const float &y, const float &z);

	XieMatrix view(const XieVector &eye, const XieVector &lookAt, const XieVector &up);

	//fov needs to be an angle in radians
	XieMatrix project(const float &fov, const float &aspect, const float &near, const float &far);
}
