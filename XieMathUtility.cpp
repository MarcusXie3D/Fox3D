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

XieTexcoord XieMathUtility::lerp(const XieTexcoord &v1, const XieTexcoord &v2, const float &coe) {
	return XieTexcoord(
		lerp(v1.u, v2.u, coe),
		lerp(v1.v, v2.v, coe)
	);
}

XieVertex XieMathUtility::lerp(const XieVertex &v1, const XieVertex &v2, const float &coe, const bool &texMode) {
	if(texMode)
		return XieVertex(
			lerp(v1.pos, v2.pos, coe),
			XieColor(),
			lerp(v1.oneOverZ, v2.oneOverZ, coe),
			lerp(v1.uv, v2.uv, coe)
		);
	else
		return XieVertex(
			lerp(v1.pos, v2.pos, coe),
			lerp(v1.color, v2.color, coe),
			lerp(v1.oneOverZ, v2.oneOverZ, coe)
		);
}

float XieMathUtility::maximum(float a, float b) {
	if (b > a)
		return b;
	else
		return a;
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

XieMatrix XieMathUtility::transpose(const XieMatrix& mat) {
	return XieMatrix(
		mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
		mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
		mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
		mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
	);
}

float XieMathUtility::determinant(const XieMatrix& mat) {
	float odet =
		mat.m[0][0] * mat.m[1][1] * mat.m[2][2] * mat.m[3][3] - mat.m[0][0] * mat.m[1][1] * mat.m[2][3] * mat.m[3][2] -
		mat.m[0][0] * mat.m[1][2] * mat.m[2][1] * mat.m[3][3] + mat.m[0][0] * mat.m[1][2] * mat.m[2][3] * mat.m[3][1] +

		mat.m[0][0] * mat.m[1][3] * mat.m[2][1] * mat.m[3][2] - mat.m[0][0] * mat.m[1][3] * mat.m[2][2] * mat.m[3][1] -
		mat.m[0][1] * mat.m[1][0] * mat.m[2][2] * mat.m[3][3] + mat.m[0][1] * mat.m[1][0] * mat.m[2][3] * mat.m[3][2] +

		mat.m[0][1] * mat.m[1][2] * mat.m[2][0] * mat.m[3][3] - mat.m[0][1] * mat.m[1][2] * mat.m[2][3] * mat.m[3][0] -
		mat.m[0][1] * mat.m[1][3] * mat.m[2][0] * mat.m[3][2] + mat.m[0][1] * mat.m[1][3] * mat.m[2][2] * mat.m[3][0] +

		mat.m[0][2] * mat.m[1][0] * mat.m[2][1] * mat.m[3][3] - mat.m[0][2] * mat.m[1][0] * mat.m[2][3] * mat.m[3][1] -
		mat.m[0][2] * mat.m[1][1] * mat.m[2][0] * mat.m[3][3] + mat.m[0][2] * mat.m[1][1] * mat.m[2][3] * mat.m[3][0] +

		mat.m[0][2] * mat.m[1][3] * mat.m[2][0] * mat.m[3][1] - mat.m[0][2] * mat.m[1][3] * mat.m[2][1] * mat.m[3][0] -
		mat.m[0][3] * mat.m[1][0] * mat.m[2][1] * mat.m[3][2] + mat.m[0][3] * mat.m[1][0] * mat.m[2][2] * mat.m[3][1] +

		mat.m[0][3] * mat.m[1][1] * mat.m[2][0] * mat.m[3][2] - mat.m[0][3] * mat.m[1][1] * mat.m[2][2] * mat.m[3][0] -
		mat.m[0][3] * mat.m[1][2] * mat.m[2][0] * mat.m[3][1] + mat.m[0][3] * mat.m[1][2] * mat.m[2][1] * mat.m[3][0];

	return odet;
}

float XieMathUtility::adjElem(
	const float &a1, const float &a2, const float &a3,
	const float &b1, const float &b2, const float &b3,
	const float &c1, const float &c2, const float &c3) {
	return a1*(b2*c3 - c2*b3) - a2*(b1*c3 - c1*b3) + a3*(b1*c2 - c1*b2);
}

XieMatrix XieMathUtility::adjoint(const XieMatrix& mat) {
	float a1 = adjElem(mat.m[1][1], mat.m[1][2], mat.m[1][3], mat.m[2][1], mat.m[2][2], mat.m[2][3], mat.m[3][1], mat.m[3][2], mat.m[3][3]);
	float a2 = adjElem(mat.m[1][0], mat.m[1][2], mat.m[1][3], mat.m[2][0], mat.m[2][2], mat.m[2][3], mat.m[3][0], mat.m[3][2], mat.m[3][3]);
	float a3 = adjElem(mat.m[1][0], mat.m[1][1], mat.m[1][3], mat.m[2][0], mat.m[2][1], mat.m[2][3], mat.m[3][0], mat.m[3][1], mat.m[3][3]);
	float a4 = adjElem(mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[3][0], mat.m[3][1], mat.m[3][2]);
	float b1 = adjElem(mat.m[0][1], mat.m[0][2], mat.m[0][3], mat.m[2][1], mat.m[2][2], mat.m[2][3], mat.m[3][1], mat.m[3][2], mat.m[3][3]);
	float b2 = adjElem(mat.m[0][0], mat.m[0][2], mat.m[0][3], mat.m[2][0], mat.m[2][2], mat.m[2][3], mat.m[3][0], mat.m[3][2], mat.m[3][3]);
	float b3 = adjElem(mat.m[0][0], mat.m[0][1], mat.m[0][3], mat.m[2][0], mat.m[2][1], mat.m[2][3], mat.m[3][0], mat.m[3][1], mat.m[3][3]);
	float b4 = adjElem(mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[3][0], mat.m[3][1], mat.m[3][2]);
	float c1 = adjElem(mat.m[0][1], mat.m[0][2], mat.m[0][3], mat.m[1][1], mat.m[1][2], mat.m[1][3], mat.m[3][1], mat.m[3][2], mat.m[3][3]);
	float c2 = adjElem(mat.m[0][0], mat.m[0][2], mat.m[0][3], mat.m[1][0], mat.m[1][2], mat.m[1][3], mat.m[3][0], mat.m[3][2], mat.m[3][3]);
	float c3 = adjElem(mat.m[0][0], mat.m[0][1], mat.m[0][3], mat.m[1][0], mat.m[1][1], mat.m[1][3], mat.m[3][0], mat.m[3][1], mat.m[3][3]);
	float c4 = adjElem(mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[3][0], mat.m[3][1], mat.m[3][2]);
	float d1 = adjElem(mat.m[0][1], mat.m[0][2], mat.m[0][3], mat.m[1][1], mat.m[1][2], mat.m[1][3], mat.m[2][1], mat.m[2][2], mat.m[2][3]);
	float d2 = adjElem(mat.m[0][0], mat.m[0][2], mat.m[0][3], mat.m[1][0], mat.m[1][2], mat.m[1][3], mat.m[2][0], mat.m[2][2], mat.m[2][3]);
	float d3 = adjElem(mat.m[0][0], mat.m[0][1], mat.m[0][3], mat.m[1][0], mat.m[1][1], mat.m[1][3], mat.m[2][0], mat.m[2][1], mat.m[2][3]);
	float d4 = adjElem(mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[2][0], mat.m[2][1], mat.m[2][2]);

	XieMatrix omat(
		a1, -a2, a3, -a4,
		-b1, b2, -b3, b4,
		c1, -c2, c3, -c4,
		-d1, d2, -d3, d4
	);
	return transpose(omat);
}

XieMatrix XieMathUtility::inverse(const XieMatrix &mat) {
	float det = fabs(determinant(mat));
	XieMatrix adj = adjoint(mat);
	XieMatrix oInverse;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			oInverse.m[i][j] = adj.m[i][j] / det;
		}

	return oInverse;
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
