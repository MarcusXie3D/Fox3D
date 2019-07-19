#include "RenderBox.h"
#include "Screen.h"
#include "Math.h"
#include "DeviceContext.h"

#include <iostream> // for Debug

extern const float width, height;
extern const float PI;

RenderBox::RenderBox(Device *device) : m_device(device) {
	m_deviceContext = new DeviceContext(device);
	m_shader = new Shader();
	m_deviceContext->setShader(m_shader);

	m_matScale = XieMathUtility::scale(1.f, 1.f, 1.f);
	m_matRotate = XieMathUtility::rotate(1.f, 0.f, 0.f, 0.f);
	m_matTranslate = XieMathUtility::translate(0.f, 0.f, -5.f);

	m_matModel = m_matTranslate * m_matRotate * m_matScale;
	float aspect = width / height;
	XieMatrix matProject = XieMathUtility::project(PI * 0.5f, aspect, 1.f, 500.f);
	XieVector cameraPos(15, 0, 0, 1);
	XieVector lookAt(0, 0, 0, 1);
	XieVector up(0, 0, 1, 1);
	XieMatrix matView = XieMathUtility::view(cameraPos, lookAt, up);
	m_matVP = matProject * matView;
	m_matMVP = m_matVP * m_matModel;

	//// Debug section begins
	//XieVector vec(0.5f, 0.5f, 0.5f, 1.f);
	//XieVector vecDub(1.f, 1.f, 1.f, 1.f);
	//vec = m_matMVP * vec;
	//vecDub = m_matMVP * vecDub;

	//std::cout << "one" << ' ';
	//std::cout << vec.x << ' ';
	//std::cout << vec.y << ' ';
	//std::cout << vec.z << ' ';
	//std::cout << vec.w << ' ';
	//std::cout << '\n';

	//std::cout << "two" << ' ';
	//std::cout << vecDub.x << ' ';
	//std::cout << vecDub.y << ' ';
	//std::cout << vecDub.z << ' ';
	//std::cout << vecDub.w << ' ';
	//std::cout << '\n';
	//std::cout << '\n';
	//// Debug section ends

	m_shader->setMatMVP(m_matMVP);
}

void RenderBox::update() {
	bool flagScale{ false };
	bool flagRotate{ false };

	if (Screen::m_keys[VK_DOWN]) {
		if (m_elongate > 0.01f) {
			m_elongate -= 0.01f;
			flagScale = true;
		}
	}
	if (Screen::m_keys[VK_UP]) {
		m_elongate += 0.01f;
		flagScale = true;
	}
	if (Screen::m_keys[VK_LEFT]) {
		m_rotateAngle += 0.01f;
		flagRotate = true;
	}
	if (Screen::m_keys[VK_RIGHT]) {
		m_rotateAngle -= 0.01f;
		flagRotate = true;
	}

	if(flagScale)
		m_matScale = XieMathUtility::scale(1.f, m_elongate, 1.f);
	if (flagRotate)
		m_matRotate = XieMathUtility::rotate(-1, -0.5, 1, m_rotateAngle);
	if (flagScale || flagRotate) {
		m_matModel = m_matTranslate * m_matRotate * m_matScale;
		m_matMVP = m_matVP * m_matModel;
		m_shader->setMatMVP(m_matMVP);
	}
}

void RenderBox::render() {
	//m_deviceContext->drawTriangle(m_triangle); //for Debug

	m_deviceContext->setBuffer(m_boxData);
	m_deviceContext->setIndices(m_indices);
	m_deviceContext->draw();
}

void RenderBox::clear() {
	if (m_deviceContext)
		delete m_deviceContext;
	if (m_shader)
		delete m_shader;
}
