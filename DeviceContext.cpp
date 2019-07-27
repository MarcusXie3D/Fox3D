#include "DeviceContext.h"
#include <array>
#include <vector>

extern const float width, height;

DeviceContext::DeviceContext(Device *device) : m_device(device) {}

void DeviceContext::setShader(Shader *shader) {
	m_shader = shader;
}
void DeviceContext::setBuffer(std::vector<XieVertex> buffer) {
	m_buffer = buffer;
}

void DeviceContext::setIndices(std::vector<int> indices) {
	m_indices = indices;
}

void DeviceContext::setNormals(std::vector<XieVector> normals) {
	m_normals = normals;
}

void DeviceContext::setTexcoords(std::vector<XieTexcoord> texcoords) {
	m_texcoords = texcoords;
}

void DeviceContext::drawTriangle(XieVertex &v1, XieVertex &v2, XieVertex &v3, XieVector normal) {
	m_shader->faceShader(normal);

	if (v2.pos.y == v3.pos.y) {
		if (v2.pos.x > v3.pos.x) {
			XieVertex temp = v2;
			v2 = v3;
			v3 = temp;
		}

		if (v1.pos.y < v2.pos.y)
			drawUpward(v1, v2, v3);
		else
			drawDownward(v1, v2, v3);
	}
	else if (v1.pos.y == v2.pos.y) {
		if (v1.pos.x > v2.pos.x) {
			XieVertex temp = v1;
			v1 = v2;
			v2 = temp;
		}

		if (v3.pos.y < v1.pos.y)
			drawUpward(v3, v1, v2);
		else
			drawDownward(v3, v1, v2);
	}
	else if (v1.pos.y == v3.pos.y) {
		if (v1.pos.x > v3.pos.x) {
			XieVertex temp = v1;
			v1 = v3;
			v3 = temp;
		}

		if (v2.pos.y < v1.pos.y)
			drawUpward(v2, v1, v3);
		else
			drawDownward(v2, v1, v3);
	}
	else {
		std::array<XieVertex, 3> verts{ v1, v2, v3 };
		std::sort(verts.begin(), verts.end(), [](const XieVertex &a,
			const XieVertex &b) {
			return a.pos.y < b.pos.y;
		});

		XieVertex top = verts[0];
		XieVertex middle = verts[1];
		XieVertex bottom = verts[2];
		XieVertex middleLevel = XieMathUtility::lerp(top, bottom, (middle.pos.y - top.pos.y) / (bottom.pos.y - top.pos.y), m_texMode);

		if (middle.pos.x > middleLevel.pos.x) {
			XieVertex temp = middle;
			middle = middleLevel;
			middleLevel = temp;
		}

		drawUpward(top, middle, middleLevel);
		drawDownward(bottom, middle, middleLevel);
	}
}

void DeviceContext::transformClip2NDC(XieVertex &vert) {
	float inv = 1.f / vert.pos.w;
	vert.pos.x *= inv;
	vert.pos.y *= inv;
	vert.pos.z *= inv;
	vert.pos.w = 1.0f;
}

void DeviceContext::transformNDC2screen(XieVertex &vert) {
	float map = (vert.pos.x + 1.f) / 2.f;
	vert.pos.x = width * map;
	map = 1.f - ((vert.pos.y + 1.f) / 2.f);
	vert.pos.y = height * map;
}

void DeviceContext::drawScanline(const XieVertex &left, const XieVertex &right, const int &yRaster) {
	int leftRaster = static_cast<int>(left.pos.x + 0.5f);
	int rightRaster = static_cast<int>(right.pos.x + 0.5f);
	float lineLengthRaster = static_cast<float>(rightRaster - leftRaster);
	for (int xRaster = leftRaster; xRaster <= rightRaster; xRaster++) {
		float coe = static_cast<float>(xRaster - leftRaster) / lineLengthRaster;
		float oneOverZ = XieMathUtility::lerp(left.oneOverZ, right.oneOverZ, coe);
		if (oneOverZ > m_device->getZbuffer(xRaster, yRaster)) {
			m_device->setZbuffer(xRaster, yRaster, oneOverZ);
			XieVertex vert = XieMathUtility::lerp(left, right, coe, m_texMode);
			float Z = 1.f / oneOverZ;
			vert.color *= Z;
			vert.uv *= Z;
			m_device->drawPixel(xRaster, yRaster, m_shader->fragmentShader(vert, m_texMode));
		}
	}
}

void DeviceContext::drawUpward(XieVertex &v1, const XieVertex &v2, const XieVertex &v3) {
	float dy = 0.f;
	v1.pos.y -= 1.f;
	float yRangeFormer = v2.pos.y - v1.pos.y;
	for (float yFormer = v1.pos.y; yFormer < v2.pos.y + 1.f; yFormer += 1.f) {
		int yRaster = static_cast<int>(yFormer + 0.5f);
		float coe = dy / yRangeFormer;
		if (coe > 1.f)
			coe = 1.f;
		XieVertex endpointLeft = XieMathUtility::lerp(v1, v2, coe, m_texMode);
		XieVertex endpointRight = XieMathUtility::lerp(v1, v3, coe, m_texMode);
		drawScanline(endpointLeft, endpointRight, yRaster);
		dy += 1.f;
	}
}

void DeviceContext::drawDownward(XieVertex &v1, const XieVertex &v2, const XieVertex &v3) {
	float dy = 0.f;
	v1.pos.y += 1.f;
	float yRangeFormer = v1.pos.y - v2.pos.y;
	for (float yFormer = v1.pos.y; yFormer > v2.pos.y; yFormer -= 1.f) {
		int yRaster = static_cast<int>(yFormer + 0.5f);
		float coe = dy / yRangeFormer;
		if (coe > 1.f)
			coe = 1.f;
		XieVertex endpointLeft = XieMathUtility::lerp(v1, v2, coe, m_texMode);
		XieVertex endpointRight = XieMathUtility::lerp(v1, v3, coe, m_texMode);
		drawScanline(endpointLeft, endpointRight, yRaster);
		dy += 1.f;
	}
}

bool DeviceContext::cullBackface(const XieVertex &v1, const XieVertex &v2, const XieVertex &v3) {
	XieVector vec1 = v3.pos - v2.pos;
	XieVector vec2 = v2.pos - v1.pos;
	XieVector normal = XieMathUtility::cross(vec1, vec2);
	if (normal.z < 0.f)
		return false;
	else
		return true;
}

void DeviceContext::switchMode() {
	m_texMode = !m_texMode;
}

void DeviceContext::draw() {
	for (auto &element : m_buffer)
		m_shader->vertexShader(element);

	int tri = 0;
	int normalIndex = -1;
	std::array<XieVertex, 3> v;
	for (unsigned int i = 0; i < m_indices.size(); i++) {
		v[tri] = m_buffer[m_indices[i]];
		if (m_texMode)
			v[tri].uv = m_texcoords[i];

		if (tri == 2) {
			tri = 0;
			normalIndex++;

			if (cullBackface(v[0], v[1], v[2]))
				continue;

			for (unsigned int j = 0; j < 3; j++) {
				v[j].oneOverZ = 1.f / v[j].pos.w;
				v[j].color *= v[j].oneOverZ;
				if(m_texMode)
					v[j].uv *= v[j].oneOverZ;

				transformClip2NDC(v[j]);
				transformNDC2screen(v[j]);
			}

			drawTriangle(v[0], v[1], v[2], m_normals[normalIndex]);
		}
		else
			tri++;
	}
}
