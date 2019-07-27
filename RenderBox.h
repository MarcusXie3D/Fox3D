#pragma once

#include <vector>
#include "Device.h"
#include "DeviceContext.h"
#include "Math.h"
#include "Shader.h"
#include "Texture.h"

// Palette         R            G           B
#define IVORY 0.94140625f, 0.9765625f, 0.9296875f
#define NAVY 0.11328125f, 0.20703125f, 0.33984375f
#define	DIRTY_AZURE 0.0546875f, 0.37109375f, 0.609375f
#define TENDER_GREEN 0.7109375f, 0.85546875f, 0.58203125f
#define MILD_ORANGE 0.94140625f, 0.59765625f, 0.16796875f

class RenderBox {
private:
	float m_rotateAngle = 1.f;
	float m_scale = 2.f;
	float m_elongate = m_scale;

	XieMatrix m_matScale;
	XieMatrix m_matRotate;
	XieMatrix m_matTranslate;
	XieMatrix m_matModel;
	XieMatrix m_matVP;
	XieMatrix m_matMVP;

	XieColor m_lightColor = XieColor(1.f, 1.f, 1.f, 1.f);
	XieVector m_lightDir = XieVector(-3.f, -3.f, 4.f, 1);

	Device *m_device;
	DeviceContext *m_deviceContext;
	Shader *m_shader;
	Texture m_tex;

	std::vector<XieVertex> m_boxData = {
		XieVertex(XieVector(1, -1, 1, 1), XieColor(TENDER_GREEN)),
		XieVertex(XieVector(-1, -1, 1, 1), XieColor(MILD_ORANGE)),
		XieVertex(XieVector(-1, 1, 1, 1), XieColor(TENDER_GREEN)),
		XieVertex(XieVector(1, 1, 1, 1), XieColor(MILD_ORANGE)),
		XieVertex(XieVector(1, -1, -1, 1), XieColor(MILD_ORANGE)),
		XieVertex(XieVector(-1, -1, -1, 1), XieColor(TENDER_GREEN)),
		XieVertex(XieVector(-1, 1, -1, 1), XieColor(MILD_ORANGE)),
		XieVertex(XieVector(1, 1, -1, 1), XieColor(TENDER_GREEN))
	};

	std::vector<int> m_indices = {
		0, 2, 1,
		0, 3, 2,

		4, 5, 6,
		4, 6, 7,

		0, 1, 5,
		0, 5, 4,
		
		1, 6, 5,
		1, 2, 6,

		2, 7, 6,
		2, 3, 7,

		3, 4, 7,
		3, 0, 4
	};

	std::vector<XieTexcoord> m_texcoords = {
		XieTexcoord(0, 0), XieTexcoord(1, 1), XieTexcoord(0, 1),
		XieTexcoord(0, 0), XieTexcoord(1, 0), XieTexcoord(1, 1),

		XieTexcoord(0, 0), XieTexcoord(0, 1), XieTexcoord(1, 1),
		XieTexcoord(0, 0), XieTexcoord(1, 1), XieTexcoord(1, 0),

		XieTexcoord(0, 0), XieTexcoord(0, 1), XieTexcoord(1, 1),
		XieTexcoord(0, 0), XieTexcoord(1, 1), XieTexcoord(1, 0),

		XieTexcoord(0, 0), XieTexcoord(1, 1), XieTexcoord(1, 0),
		XieTexcoord(0, 0), XieTexcoord(0, 1), XieTexcoord(1, 1),

		XieTexcoord(0, 0), XieTexcoord(1, 1), XieTexcoord(1, 0),
		XieTexcoord(0, 0), XieTexcoord(0, 1), XieTexcoord(1, 1),

		XieTexcoord(0, 0), XieTexcoord(1, 1), XieTexcoord(1, 0),
		XieTexcoord(0, 0), XieTexcoord(0, 1), XieTexcoord(1, 1)
	};

	std::vector<XieVector> m_normals = {
		XieVector(0, 0, 1, 0),
		XieVector(0, 0, 1, 0),

		XieVector(0, 0, -1, 0),
		XieVector(0, 0, -1, 0),

		XieVector(0, -1, 0, 0),
		XieVector(0, -1, 0, 0),

		XieVector(-1, 0, 0, 0),
		XieVector(-1, 0, 0, 0),

		XieVector(0, 1, 0, 0),
		XieVector(0, 1, 0, 0),

		XieVector(1, 0, 0, 0),
		XieVector(1, 0, 0, 0)
	};

public:
	RenderBox(Device *device, std::wstring filePath);

	void update();

	void render();

	void clear();
};
