#pragma once

class XieVector {
public:
	float x;
	float y;
	float z;
	float w;

public:
	XieVector() {}
	XieVector(float p_x, float p_y, float p_z, float p_w = 0.f) : x(p_x), y(p_y), z(p_z), w(p_w) {}

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
	XieColor(float p_r = 1.f, float p_g = 1.f, float p_b = 1.f, float p_a = 1.f) : r(p_r), g(p_g), b(p_b), a(p_a) {}

	XieColor& operator= (const XieColor& p_v);

	XieColor operator+ (const XieColor& p_v);

	XieColor operator* (const float& p_v);

	XieColor operator* (const XieColor& p_v);

	XieColor& operator*= (const float& p_v);
};
