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

	XieVector& operator= (const XieVector& p_v) {
		if (this == &p_v)
			return *this;
		this->x = p_v.x;
		this->y = p_v.y;
		this->z = p_v.z;
		this->w = p_v.w;
		return *this;
	}

	XieVector& operator- (const XieVector& p_v) const {
		return XieVector(
			x - p_v.x,
			y - p_v.y,
			z - p_v.z
		);
	}
};

class XieColor {
public:
	float r;
	float g;
	float b;
	float a;

public:
	XieColor(float p_r = 255.f, float p_g = 255.f, float p_b = 255.f, float p_a = 255.f) : r(p_r), g(p_g), b(p_b), a(p_a) {}

	XieColor& operator= (const XieColor& p_v) {
		if (this == &p_v)
			return *this;
		this->r = p_v.r;
		this->g = p_v.g;
		this->b = p_v.b;
		this->a = p_v.a;
		return *this;
	}

	XieColor& operator*= (const float& p_v) {
		this->r = this->r * p_v;
		this->g = this->g * p_v;
		this->b = this->b * p_v;
		this->a = this->a * p_v;
		return *this;
	}
};
