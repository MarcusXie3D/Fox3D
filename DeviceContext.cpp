#include "DeviceContext.h"
#include <array>
#include <vector>
#include <iostream> //for Debug
#include <windows.h>// for Debug

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

void DeviceContext::drawTriangle(XieVertex &v1, XieVertex &v2, XieVertex &v3) {
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
		XieVertex middleLevel = XieMathUtility::lerp(top, bottom, (middle.pos.y - top.pos.y) / (bottom.pos.y - top.pos.y));

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
	//// Debug begins
	//if (left.pos.x >= 0 && left.pos.x < width && right.pos.x >= 0 && right.pos.x < width)
	//	;
	//else
	//	std::cout << left.pos.x << " " << right.pos.x << '\n';
	//// Debug ends
	int leftRaster = static_cast<int>(left.pos.x + 0.5f);
	int rightRaster = static_cast<int>(right.pos.x + 0.5f);
	float lineLengthRaster = static_cast<float>(rightRaster - leftRaster);
	for (int xRaster = leftRaster; xRaster <= rightRaster; xRaster++) {
		float coe = static_cast<float>(xRaster - leftRaster) / lineLengthRaster;
		float oneOverZ = XieMathUtility::lerp(left.oneOverZ, right.oneOverZ, coe);
		if (oneOverZ > m_device->getZbuffer(xRaster, yRaster)) {
			m_device->setZbuffer(xRaster, yRaster, oneOverZ);
			XieVertex vert = XieMathUtility::lerp(left, right, coe);
			float Z = 1.f / oneOverZ;
			vert.color *= Z;
			// over here, lay other properties of vert
			m_device->drawPixel(xRaster, yRaster, m_shader->fragmentShader(vert));
		}
	}
}

void DeviceContext::drawUpward(const XieVertex &v1, const XieVertex &v2, const XieVertex &v3) {
	float dy = 0.f;
	float yRangeFormer = v2.pos.y - v1.pos.y;
	for (float yFormer = v1.pos.y; yFormer < v2.pos.y + 1.f; yFormer += 1.f) {
		int yRaster = static_cast<int>(yFormer + 0.5f);
		float coe = dy / yRangeFormer;
		if (coe > 1.f)
			coe = 1.f;
		XieVertex endpointLeft = XieMathUtility::lerp(v1, v2, coe);
		XieVertex endpointRight = XieMathUtility::lerp(v1, v3, coe);
		drawScanline(endpointLeft, endpointRight, yRaster);
		dy += 1.f;
	}
}

void DeviceContext::drawDownward(const XieVertex &v1, const XieVertex &v2, const XieVertex &v3) {
	float dy = 0.f;
	float yRangeFormer = v1.pos.y - v2.pos.y;
	for (float yFormer = v1.pos.y; yFormer > v2.pos.y; yFormer -= 1.f) {
		int yRaster = static_cast<int>(yFormer + 0.5f);
		float coe = dy / yRangeFormer;
		XieVertex endpointLeft = XieMathUtility::lerp(v1, v2, coe);
		XieVertex endpointRight = XieMathUtility::lerp(v1, v3, coe);
		drawScanline(endpointLeft, endpointRight, yRaster);
		dy += 1.f;
	}
}

void DeviceContext::draw() {
	//static bool flagT = true;//for Debug

	for (auto &element : m_buffer)
		m_shader->vertexShader(element);

	//if (flagT) {//for Debug
	//	for (auto const &element : m_buffer) {
	//		std::cout << element.pos.x << ' ';
	//		std::cout << element.pos.y << ' ';
	//		std::cout << element.pos.z << ' ';
	//		std::cout << element.pos.w << ' ';
	//		std::cout << '\n';
	//	}

	//	flagT = false;
	//}

	//Viewing Frustum Clipping is left here

	for (auto &element : m_buffer) {
		element.oneOverZ = 1.f / element.pos.w;
		element.color *= element.oneOverZ;
		// over here, add other properties of the vertexl

		transformClip2NDC(element);
		transformNDC2screen(element);
	}

	int tri = 0;
	XieVertex v1, v2, v3;
	for (unsigned int i = 0; i < m_indices.size(); i++) {
		if (tri == 0)
			v1 = m_buffer[m_indices[i]];
		else if(tri == 1)
			v2 = m_buffer[m_indices[i]];
		else if(tri == 2)
			v3 = m_buffer[m_indices[i]];

		if (tri == 2) {
			tri = 0;
			//std::cout << "3oneOverZs : " << v1.oneOverZ << " " << v2.oneOverZ << " " << v3.oneOverZ << "\n";// for Debug
			drawTriangle(v1, v2, v3);
		}
		else
			tri++;
	}
}
