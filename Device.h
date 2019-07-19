#pragma once
#include"Math.h"

class Device {
public:
	Device(void *fb, int width, int height);

	~Device();

	void clear();

	void drawPixel(const int &x, const int &y, const XieColor &color);

private:
	//transform_t transform;      // 坐标变换器
	int m_width;                  // 窗口宽度
	int m_height;                 // 窗口高度
	IUINT32 **m_framebuffer;      // 像素缓存：framebuffer[y] 代表第 y行
	//float **zbuffer;            // 深度缓存：zbuffer[y] 为第 y行指针
	//IUINT32 **texture;          // 纹理：同样是每行索引
	//int tex_width;              // 纹理宽度
	//int tex_height;             // 纹理高度
	//float max_u;                // 纹理最大宽度：tex_width - 1
	//float max_v;                // 纹理最大高度：tex_height - 1
	//int render_state;           // 渲染状态
	XieColor m_foreground;
	XieColor m_background;

private:
	IUINT32 gdiColorTransform(XieColor color);
};
