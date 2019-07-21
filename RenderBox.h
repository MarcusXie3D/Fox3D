#pragma once

#include <vector>
#include "Device.h"
#include "DeviceContext.h"
#include "Math.h"
#include "Shader.h"

class RenderBox {
private:
	float m_rotateAngle = 1.f;
	float m_scale = 3.f;
	float m_elongate = m_scale;

	XieMatrix m_matScale;
	XieMatrix m_matRotate;
	XieMatrix m_matTranslate;
	XieMatrix m_matModel;
	XieMatrix m_matVP;
	XieMatrix m_matMVP;

	Device *m_device;
	DeviceContext *m_deviceContext;
	Shader *m_shader;

	XieTriangle m_triangle = XieTriangle(
		XieVertex(XieVector(0.0f, 0.39f, 0.0f), XieColor(0, 0, 255)),
		XieVertex(XieVector(0.95f, -0.35f, 0.0f), XieColor(0, 255, 0)),
		XieVertex(XieVector(-0.46f, -0.8f, 0.0f), XieColor(255, 0, 0))
	);

	std::vector<XieVertex> m_boxData = {
		XieVertex(XieVector(2, -2, 2, 2), XieColor(255, 0, 0)),
		XieVertex(XieVector(-2, -2, 2, 2), XieColor(0, 0, 255)),
		XieVertex(XieVector(-2, 2, 2, 2), XieColor(255, 0, 0)),
		XieVertex(XieVector(2, 2, 2, 2), XieColor(0, 0, 255)),
		XieVertex(XieVector(2, -2, -2, 2), XieColor(0, 0, 255)),
		XieVertex(XieVector(-2, -2, -2, 2), XieColor(255, 0, 0)),
		XieVertex(XieVector(-2, 2, -2, 2), XieColor(0, 0, 255)),
		XieVertex(XieVector(2, 2, -2, 2), XieColor(255, 0, 0))
	};
	/*XieVertex(XieVector(1, -1, 1, 1), XieColor(255, 0, 0)),
		XieVertex(XieVector(-1, -1, 1, 1), XieColor(0, 0, 255)),
		XieVertex(XieVector(-1, 1, 1, 1), XieColor(255, 0, 0)),
		XieVertex(XieVector(1, 1, 1, 1), XieColor(0, 0, 255)),
		XieVertex(XieVector(1, -1, -1, 1), XieColor(0, 0, 255)),
		XieVertex(XieVector(-1, -1, -1, 1), XieColor(255, 0, 0)),
		XieVertex(XieVector(-1, 1, -1, 1), XieColor(0, 0, 255)),
		XieVertex(XieVector(1, 1, -1, 1), XieColor(255, 0, 0))*/
	/*XieVertex(XieVector(0.5, -0.5, 0.5, 1), XieColor(255, 0, 0)),
		XieVertex(XieVector(-0.5, -0.5, 0.5, 1), XieColor(0, 0, 255)),
		XieVertex(XieVector(-0.5, 0.5, 0.5, 1), XieColor(255, 0, 0)),
		XieVertex(XieVector(0.5, 0.5, 0.5, 1), XieColor(0, 0, 255)),
		XieVertex(XieVector(0.5, -0.5, -0.5, 1), XieColor(0, 0, 255)),
		XieVertex(XieVector(-0.5, -0.5, -0.5, 1), XieColor(255, 0, 0)),
		XieVertex(XieVector(-0.5, 0.5, -0.5, 1), XieColor(0, 0, 255)),
		XieVertex(XieVector(0.5, 0.5, -0.5, 1), XieColor(255, 0, 0))*/

	std::vector<int> m_indices = {
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		0, 4, 5,
		0, 5, 1,
		
		1, 5, 6,
		1, 6, 2,

		2, 6, 7,
		2, 7, 3,

		3, 7, 4,
		3, 4, 0
	};

public:
	RenderBox(Device *device);

	void update();

	void render();

	void clear();
};
