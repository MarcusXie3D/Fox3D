#include "XieVector.h"
#include <math.h>

float XieVector::getLength() {
	return sqrt(x * x + y * y + z * z);
}

void XieVector::normalize() {
	float length = getLength();
	if (length != 0.f) {
		float inv = 1.f / getLength();
		x *= inv;
		y *= inv;
		z *= inv;
	}
}

XieVector& XieVector::operator= (const XieVector& p_v) {
	if (this == &p_v)
		return *this;
	this->x = p_v.x;
	this->y = p_v.y;
	this->z = p_v.z;
	this->w = p_v.w;
	return *this;
}

XieVector XieVector::operator- (const XieVector& p_v) const {
	return XieVector(
		x - p_v.x,
		y - p_v.y,
		z - p_v.z
	);
}

XieVector XieVector::operator- () {
	return XieVector(-x, -y - z, w);
}

XieColor& XieColor::operator= (const XieColor& p_v) {
	if (this == &p_v)
		return *this;
	this->r = p_v.r;
	this->g = p_v.g;
	this->b = p_v.b;
	this->a = p_v.a;
	return *this;
}

XieColor XieColor::operator+ (const XieColor& p_v) {
	return XieColor(
		r + p_v.r,
		g + p_v.g,
		b + p_v.b,
		a + p_v.a
	);
}

XieColor XieColor::operator* (const float& p_v) {
	return XieColor(
		r * p_v,
		g * p_v,
		b * p_v,
		a * p_v
	);
}

XieColor XieColor::operator* (const XieColor& p_v) {
	return XieColor(
		r * p_v.r,
		g * p_v.g,
		b * p_v.b,
		a * p_v.a
	);
}

XieColor& XieColor::operator*= (const float& p_v) {
	this->r = this->r * p_v;
	this->g = this->g * p_v;
	this->b = this->b * p_v;
	this->a = this->a * p_v;
	return *this;
}