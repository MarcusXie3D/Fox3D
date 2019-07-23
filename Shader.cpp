#include "Shader.h"
#include <iostream>

void Shader::setMatModel(const XieMatrix &matModel) {
	m_matModel = matModel;
}

void Shader::setMatMVP(const XieMatrix &matMVP) {
	m_matMVP = matMVP;
}

void Shader::setLightColor(const XieColor &lightColor) {
	m_lightColor = lightColor;
}

void Shader::setLightDir(const XieVector &lightDir) {
	m_lightDir = lightDir;
}

void Shader::faceShader(XieVector &normal) {
	normal = mat3(XieMathUtility::transpose(XieMathUtility::inverse(m_matModel))) * normal;
	normal.normalize();

	float ambientStrength = 0.1f;
	XieColor ambient = m_lightColor * ambientStrength;

	float diff = XieMathUtility::max(XieMathUtility::dot(normal, m_lightDir), 0.f);
	XieColor diffuse = m_lightColor * diff;

	m_faceLight = ambient + diffuse;
}

void Shader::vertexShader(XieVertex &v) {
	v.pos = m_matMVP * v.pos;
}

XieColor Shader::fragmentShader(XieVertex &v) {
	return m_faceLight * v.color;
}
