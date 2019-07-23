#pragma once

#include "Math.h"

class Shader {
private:
	XieMatrix m_matModel;
	XieMatrix m_matMVP;
	XieColor m_lightColor;
	XieVector m_lightDir;

	XieColor m_faceLight;

public:
	void setMatModel(const XieMatrix &matModel);

	void setMatMVP(const XieMatrix &matMVP);

	void setLightColor(const XieColor &lightColor);

	void setLightDir(const XieVector &lightDir);

	void faceShader(XieVector &normal);

	void vertexShader(XieVertex &v);

	XieColor fragmentShader(XieVertex &v);
};
