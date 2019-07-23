#include "Math.h"
#include "Device.h"
#include <iostream>
#include <cassert>
#include <cstddef>
#include <limits>

Device::Device(void *fb, int width, int height) : m_width(width), m_height(height) {
	int need = sizeof(void*) * (height * 2 + 1024) + width * height * 8;
	char *ptr = new char[need + 64];//(char*)malloc(need + 64);
	char *framebuf, *zbuf;
	int j;
	assert(ptr);
	m_framebuffer = (IUINT32**)ptr;
	m_zbuffer = (float**)(ptr + sizeof(void*) * height);
	ptr += sizeof(void*) * height * 2;
	//device->texture = (IUINT32**)ptr;
	ptr += sizeof(void*) * 1024;
	framebuf = (char*)ptr;
	zbuf = (char*)ptr + width * height * 4;
	ptr += width * height * 8;
	if (fb != nullptr) framebuf = (char*)fb;
	for (j = 0; j < height; j++) {
		m_framebuffer[j] = (IUINT32*)(framebuf + width * 4 * j);
		m_zbuffer[j] = (float*)(zbuf + width * 4 * j);
	}
	//device->texture[0] = (IUINT32*)ptr;
	//device->texture[1] = (IUINT32*)(ptr + 16);
	//memset(device->texture[0], 0, 64);
	//device->tex_width = 2;
	//device->tex_height = 2;
	//device->max_u = 1.0f;
	//device->max_v = 1.0f;
	m_foreground = XieColor(0.f, 1.f, 0.f);
	m_background = XieColor(0.f, 0.f, 0.f);
	//transform_init(&device->transform, width, height);
	//device->render_state = RENDER_STATE_WIREFRAME;
}

Device::~Device() {
	if (m_framebuffer)
		delete[] m_framebuffer;
	m_framebuffer = nullptr;
	m_zbuffer = nullptr;
	//device->texture = NULL;
}

void Device::clear() {
	int y, x;// , height = device->height;
	for (y = 0; y < m_height; y++) {
		IUINT32 *dst = m_framebuffer[y];
		IUINT32 cc = gdiColorTransform(m_background);
		for (x = m_width; x > 0; dst++, x--) dst[0] = cc;
	}
	for (y = 0; y < m_height; y++) {
		float *dst = m_zbuffer[y];
		for (x = m_width; x > 0; dst++, x--) dst[0] = 0.f;
	}
}

IUINT32 Device::gdiColorTransform(XieColor color) {
	color *= 255.f;
	color.r = (color.r > 255.f) ? 255.f : color.r;
	color.g = (color.g > 255.f) ? 255.f : color.g;
	color.b = (color.b > 255.f) ? 255.f : color.b;

	IUINT32 r = static_cast<IUINT32>(color.r);
	IUINT32 g = static_cast<IUINT32>(color.g);
	IUINT32 b = static_cast<IUINT32>(color.b);
	return (r << 16) | (g << 8) | b;
}

float Device::getZbuffer(const int &x, const int &y) {
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
		return m_zbuffer[y][x];
	else
		return std::numeric_limits<float>::max();
}

void Device::setZbuffer(const int &x, const int &y, const float &oneOverZ) {
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
		m_zbuffer[y][x] = oneOverZ;
}

void Device::drawPixel(const int &x, const int &y, const XieColor &color) {
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
		m_framebuffer[y][x] = gdiColorTransform(color);
}
