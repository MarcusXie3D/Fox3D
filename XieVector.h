#pragma once

class XieVector {
public:
	float x;
	float y;
	float z;
	float w;

public:
	XieVector() {}
	XieVector(const float &p_x, const float &p_y, const float &p_z, const float &p_w = 0.f) : x(p_x), y(p_y), z(p_z), w(p_w) {}

	float getLength();

	void normalize();

	XieVector& operator= (const XieVector& p_v);

	XieVector operator- (const XieVector& p_v) const;

	XieVector operator- ();
};

class XieColor {
public:
	float r;
	float g;
	float b;
	float a;

public:
	XieColor(const float &p_r = 1.f, const float &p_g = 1.f, const float &p_b = 1.f, const float &p_a = 1.f) : r(p_r), g(p_g), b(p_b), a(p_a) {}

	XieColor& operator= (const XieColor& p_v);

	XieColor operator+ (const XieColor& p_v);

	XieColor operator* (const float& p_v);

	XieColor operator* (const XieColor& p_v);

	XieColor& operator*= (const float& p_v);
};

class XieTexcoord {
public:
	float u;
	float v;

public:
	XieTexcoord() = default;
	XieTexcoord(const float &p_u, const float &p_v) : u(p_u), v(p_v) {}

	XieTexcoord& operator*= (const float& p_v);
};
