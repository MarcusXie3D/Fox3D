#include "Texture.h"

Texture::Texture(const UINT &width, const UINT &height) : m_width(width), m_height(height) {
	m_buffer = new XieColor*[height];
	for (UINT i = 0; i < height; i++) {
		m_buffer[i] = new XieColor[width];
	}
}

Texture::~Texture() {
	for (UINT i = 0; i < m_height; i++) {
		delete m_buffer[i];
	}
}

Texture::Texture(const Texture& rhs) :m_width(rhs.m_width), m_height(rhs.m_height)
{
	m_buffer = new XieColor*[m_height];
	for (int i = 0; i < m_height; ++i)
	{
		m_buffer[i] = new XieColor[m_width];
	}
	for (int i = 0; i < m_width; ++i)
	{
		for (int j = 0; j < m_height; ++j)
		{
			m_buffer[j][i] = rhs.m_buffer[j][i];
		}
	}
}

Texture& Texture::operator=(const Texture& rhs)
{
	if (this == &rhs)
		return *this;
	m_width = rhs.m_width;
	m_height = rhs.m_height;
	m_buffer = new XieColor*[m_height];
	for (int i = 0; i < m_height; ++i)
	{
		m_buffer[i] = new XieColor[m_width];
	}
	for (int i = 0; i < m_width; ++i)
	{
		for (int j = 0; j < m_height; ++j)
		{
			m_buffer[j][i] = rhs.m_buffer[j][i];
		}
	}
	return *this;
}

void Texture::setBuffer(const UINT &x, const UINT &y, const XieColor &color) {
	m_buffer[y][x] = color;
}

XieColor Texture::sampleTex(const float &u, const float &v) {
	UINT x = static_cast<UINT>(u * (m_width - 1) + 0.5f);
	UINT y = static_cast<UINT>(v * (m_height - 1) + 0.5f);

	return m_buffer[y][x];
}
