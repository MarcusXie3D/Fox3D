#pragma once

#include "Math.h"

class Shader {
private:
	XieMatrix m_matMVP;
public:
	void setMatMVP(const XieMatrix &matMVP);

	void vertexShader(XieVertex &v);

	XieColor fragmentShader(XieVertex &v);
};
