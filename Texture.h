#pragma once
#include <windows.h>
#include "Math.h"

class Texture {
public:
	Texture() = default;
	Texture(const UINT &width, const UINT &height);
	~Texture();
	Texture(const Texture& rhs);
	Texture& operator=(const Texture& rhs);

	void setBuffer(const UINT &x, const UINT &y, const XieColor &color);
	XieColor sampleTex(const float &u, const float &v);

public:
	UINT m_width, m_height;
	XieColor** m_buffer;
};
