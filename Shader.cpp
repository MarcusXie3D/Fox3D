#include "Shader.h"

void Shader::setMatMVP(const XieMatrix &matMVP) {
	m_matMVP = matMVP;
}

void Shader::vertexShader(XieVertex &v) {
	v.pos = m_matMVP * v.pos;
}

XieColor Shader::fragmentShader(XieVertex &v) {
	return v.color;
}
