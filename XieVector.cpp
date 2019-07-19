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