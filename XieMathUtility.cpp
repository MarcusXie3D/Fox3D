#include "XieMathUtility.h"
#include <math.h>

float XieMathUtility::lerp(const float &v1, const float &v2, const float &coe) {
	return v1 * (1.f - coe) + v2 * coe;
}

XieVector XieMathUtility::lerp(const XieVector &v1, const XieVector &v2, const float &coe) {
	return XieVector(
		lerp(v1.x, v2.x, coe),
		lerp(v1.y, v2.y, coe),
		lerp(v1.z, v2.z, coe),
		lerp(v1.w, v2.w, coe)
	);
}

XieColor XieMathUtility::lerp(const XieColor &v1, const XieColor &v2, const float &coe) {
	return XieColor(
		lerp(v1.r, v2.r, coe),
		lerp(v1.g, v2.g, coe),
		lerp(v1.b, v2.b, coe),
		lerp(v1.a, v2.a, coe)
	);
}

XieVertex XieMathUtility::lerp(const XieVertex &v1, const XieVertex &v2, const float &coe) {
	return XieVertex(
		lerp(v1.pos, v2.pos, coe),
		lerp(v1.color, v2.color, coe),
		lerp(v1.oneOverZ, v2.oneOverZ, coe)
	);
}

float XieMathUtility::dot(const XieVector &v1, const XieVector &v2) {
	return v1.x * v2.x + v1.y*v2.y + v1.z*v2.z;
}

XieVector XieMathUtility::cross(const XieVector &v1, const XieVector &v2) {
	return XieVector(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	);
}

XieMatrix XieMathUtility::scale(const float &x, const float &y, const float &z) {
	return XieMatrix(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	);
}

//phi needs to be an angle in radians
XieMatrix XieMathUtility::rotate(const float &xAxis, const float &yAxis, const float &zAxis, const float &phi) {
	float theta = phi / 2.f;
	XieVector v(xAxis, yAxis, zAxis);
	v.normalize();
	float sine = sin(theta);
	float cosine = cos(theta);

	//Quaternion
	float x = sine * v.x;
	float y = sine * v.y;
	float z = sine * v.z;
	float w = cosine;

	return XieMatrix(
		1 - 2 * (y * y + z * z),   2 * (x * y - w * z),       2 * (x * z + w * y),       0.f,
		2 * (x * y + w * z),       1 - 2 * (x * x + z * z),   2 * (y * z - w * x),       0.f,
		2 * (x * z - w * y),       2 * (y * z + w * x),       1 - 2 * (x * x + y * y),   0.f,
		0.f,                       0.f,                       0.f,                       1.f
	);
}

XieMatrix XieMathUtility::translate(const float &x, const float &y, const float &z) {
	return XieMatrix(
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	);
}

XieMatrix XieMathUtility::view(const XieVector &eye, const XieVector &lookAt, const XieVector &up) {
	XieVector zAxis = eye - lookAt;
	zAxis.normalize();
	XieVector xAxis = cross(up, zAxis);
	xAxis.normalize();
	XieVector yAxis = cross(zAxis, xAxis);
	yAxis.normalize();

	return XieMatrix(
		xAxis.x, xAxis.y, xAxis.z, -XieMathUtility::dot(xAxis, eye),
		yAxis.x, yAxis.y, yAxis.z, -XieMathUtility::dot(yAxis, eye),
		zAxis.x, zAxis.y, zAxis.z, -XieMathUtility::dot(zAxis, eye),
		    0.f,     0.f,     0.f,                              1.f
	);
}

//fov needs to be an angle in radians
XieMatrix XieMathUtility::project(const float &fov, const float &aspect, const float &near, const float &far) {
	XieMatrix mat;
	mat.zeroOut();
	float cot = cos(fov * 0.5f) / sin(fov * 0.5f);
	mat.m[0][0] = cot / aspect;
	mat.m[1][1] = cot;
	mat.m[2][2] = -(far + near) / (far - near);
	mat.m[3][2] = -1.f;
	mat.m[2][3] = -(2 * near * far) / (far - near);
	return mat;
}
