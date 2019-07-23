#pragma once

#include "XieVector.h"

class XieMatrix {
public:
	float m[4][4];

public:
	XieMatrix() {
		identify();
	}

	XieMatrix(
		float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44
	) {
		m[0][0] = _11; m[0][1] = _12; m[0][2] = _13; m[0][3] = _14;
		m[1][0] = _21; m[1][1] = _22; m[1][2] = _23; m[1][3] = _24;
		m[2][0] = _31; m[2][1] = _32; m[2][2] = _33; m[2][3] = _34;
		m[3][0] = _41; m[3][1] = _42; m[3][2] = _43; m[3][3] = _44;
	}

public:
	void identify();

	void zeroOut();

	XieMatrix& operator=(const XieMatrix &mat);
	XieMatrix operator+(XieMatrix &mat);
	XieMatrix operator-(XieMatrix &mat);
	XieMatrix operator*(XieMatrix &mat);
	XieVector operator*(XieVector &vi);
};

class mat3 {
public:
	float m[3][3];

public:
	mat3(const XieMatrix &mat) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m[i][j] = mat.m[i][j];
			}
		}
	}

	XieVector operator*(XieVector &vi);
};
