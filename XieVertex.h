#pragma once
#include "XieVector.h"

class XieVertex {
public:
	XieVector pos;

	XieColor color;

	float oneOverZ;

	XieTexcoord uv;

public:
	XieVertex() {}
	XieVertex(XieVector p_pos, XieColor p_color, float p_oneOverZ = 1.f, XieTexcoord p_uv = XieTexcoord(0, 0)) : pos(p_pos), color(p_color), oneOverZ(p_oneOverZ), uv(p_uv) {}
	XieVertex& operator= (const XieVertex& p_vert) {
		if (this == &p_vert)
			return *this;
		this->pos = p_vert.pos;
		this->color = p_vert.color;
		this->oneOverZ = p_vert.oneOverZ;
		this->uv = p_vert.uv;
		return *this;
	}
};

class XieTriangle {
public:
	XieVertex v1;
	XieVertex v2;
	XieVertex v3;

public:
	XieTriangle() {}
	XieTriangle(XieVertex p_v1, XieVertex p_v2, XieVertex p_v3) : v1(p_v1), v2(p_v2), v3(p_v3) {}
};
