#pragma once
#include"Math.h"

class Device {
public:
	Device(void *fb, int width, int height);

	~Device();

	void clear();

	float getZbuffer(const int &x, const int &y);

	void setZbuffer(const int &x, const int &y, const float &oneOverZ);

	void drawPixel(const int &x, const int &y, const XieColor &color);

private:
	int m_width;                 
	int m_height;                
	IUINT32 **m_framebuffer;      
	float **m_zbuffer;           
	XieColor m_foreground;
	XieColor m_background;

private:
	IUINT32 gdiColorTransform(XieColor color);
};
