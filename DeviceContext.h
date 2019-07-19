#pragma once
#include "Math.h"
#include "Device.h"
#include "Shader.h"
#include <vector>

class DeviceContext {
public:
	DeviceContext(Device *device);
	void drawTriangle(XieVertex &v1, XieVertex &v2, XieVertex &v3);
	void setShader(Shader *shader);
	void setBuffer(std::vector<XieVertex> buffer);
	void setIndices(std::vector<int> indices);
	void draw();

private:
	void transformClip2NDC(XieVertex &vert);
	void transformNDC2screen(XieVertex &vert);
	void drawScanline(const XieVertex &left, const XieVertex &right, const int &yRaster);
	void drawUpward(const XieVertex &v1, const XieVertex &v2, const XieVertex &v3);
	void drawDownward(const XieVertex &v1, const XieVertex &v2, const XieVertex &v3);

private:
	Device *m_device;
	Shader *m_shader;
	std::vector<XieVertex> m_buffer;
	std::vector<int> m_indices;
};
