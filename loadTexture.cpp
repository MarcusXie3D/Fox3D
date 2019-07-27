#include "loadTexture.h"
#include <windows.h>
#include <gdiplus.h>
#include <iostream>

#include <fstream>
#include <sstream>

#pragma comment(lib, "gdiplus.lib")

Texture XieMathUtility::loadTexture(std::wstring filePath) {
	Gdiplus::GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, nullptr);

	Gdiplus::Bitmap* bmp = new Gdiplus::Bitmap(filePath.c_str());

	if (!bmp) {
		MessageBox(nullptr, "main.cpp: texture filepath is not a full path or right path!", "Error", MB_OK);
		delete bmp;
		Gdiplus::GdiplusShutdown(gdiplustoken);
		return Texture(0, 0);
	}
	else {
		UINT width = bmp->GetWidth();
		UINT height = bmp->GetHeight();

		if (width == 0 || height == 0) {
			MessageBox(nullptr, "main.cpp: texture filepath is not a full path or right path!", "Error", MB_OK);
			delete bmp;
			Gdiplus::GdiplusShutdown(gdiplustoken);
			return Texture(0, 0);
		}

		Texture tex(width, height);

		Gdiplus::Color pix;
		for (UINT i = 0; i < width; i++) {
			for (UINT j = 0; j < height; j++) {
				bmp->GetPixel(i, j, &pix);
				XieColor color(
					pix.GetRed() / 255.f,
					pix.GetGreen() / 255.f,
					pix.GetBlue() / 255.f,
					1.f
				);
				tex.setBuffer(i, j, color);
			}
		}

		delete bmp;
		Gdiplus::GdiplusShutdown(gdiplustoken);
		return tex;
	}
}