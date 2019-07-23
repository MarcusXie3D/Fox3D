#include "XieMatrix.h"

void XieMatrix::identify() {
	m[0][0] = 1.f; m[0][1] = 0.f; m[0][2] = 0.f; m[0][3] = 0.f;
	m[1][0] = 0.f; m[1][1] = 1.f; m[1][2] = 0.f; m[1][3] = 0.f;
	m[2][0] = 0.f; m[2][1] = 0.f; m[2][2] = 1.f; m[2][3] = 0.f;
	m[3][0] = 0.f; m[3][1] = 0.f; m[3][2] = 0.f; m[3][3] = 1.f;
}

void XieMatrix::zeroOut() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = 0.f;
		}
	}
}

XieMatrix& XieMatrix::operator=(const XieMatrix &mat) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = mat.m[i][j];
		}
	}
	return *this;
}

XieMatrix XieMatrix::operator+(XieMatrix &mat) {
	XieMatrix oMat;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			oMat.m[i][j] = m[i][j] + mat.m[i][j];
		}
	}
	return oMat;
}

XieMatrix XieMatrix::operator-(XieMatrix &mat) {
	XieMatrix oMat;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			oMat.m[i][j] = m[i][j] - mat.m[i][j];
		}
	}
	return oMat;
}

XieMatrix XieMatrix::operator*(XieMatrix &mat) {
	XieMatrix oMat;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			oMat.m[i][j] = m[i][0] * mat.m[0][j] +
						   m[i][1] * mat.m[1][j] +
						   m[i][2] * mat.m[2][j] +
						   m[i][3] * mat.m[3][j] ;
		}
	}
	return oMat;
}

XieVector XieMatrix::operator*(XieVector &vi) {
	XieVector vo;
	
	vo.x = m[0][0] * vi.x + m[0][1] * vi.y + m[0][2] * vi.z + m[0][3] * vi.w;
	vo.y = m[1][0] * vi.x + m[1][1] * vi.y + m[1][2] * vi.z + m[1][3] * vi.w;
	vo.z = m[2][0] * vi.x + m[2][1] * vi.y + m[2][2] * vi.z + m[2][3] * vi.w;
	vo.w = m[3][0] * vi.x + m[3][1] * vi.y + m[3][2] * vi.z + m[3][3] * vi.w;

	return vo;
}

XieVector mat3::operator*(XieVector &vi) {
	XieVector vo;

	vo.x = m[0][0] * vi.x + m[0][1] * vi.y + m[0][2] * vi.z;
	vo.y = m[1][0] * vi.x + m[1][1] * vi.y + m[1][2] * vi.z;
	vo.z = m[2][0] * vi.x + m[2][1] * vi.y + m[2][2] * vi.z;
	vo.w = 0.f;

	return vo;
}
