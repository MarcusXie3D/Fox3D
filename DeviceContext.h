#pragma once
#include "Math.h"
#include "Device.h"
#include "Shader.h"
#include <vector>

class DeviceContext {
public:
	DeviceContext(Device *device);
	void setShader(Shader *shader);
	void setBuffer(std::vector<XieVertex> buffer);
	void setIndices(std::vector<int> indices);
	void setNormals(std::vector<XieVector> normals);
	void setTexcoords(std::vector<XieTexcoord> texcoords);
	void switchMode();
	void draw();

private:
	bool cullBackface(const XieVertex &v1, const XieVertex &v2, const XieVertex &v3);
	void transformClip2NDC(XieVertex &vert);
	void transformNDC2screen(XieVertex &vert);
	void drawTriangle(XieVertex &v1, XieVertex &v2, XieVertex &v3, XieVector normal);
	void drawScanline(const XieVertex &left, const XieVertex &right, const int &yRaster);
	void drawUpward(XieVertex &v1, const XieVertex &v2, const XieVertex &v3);
	void drawDownward(XieVertex &v1, const XieVertex &v2, const XieVertex &v3);

private:
	Device *m_device;
	Shader *m_shader;
	std::vector<XieVertex> m_buffer;
	std::vector<int> m_indices;
	std::vector<XieVector> m_normals;
	bool m_texMode = true;
	std::vector<XieTexcoord> m_texcoords;
};
