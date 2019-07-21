#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>

#include "Device.h"
#include "Screen.h"
#include "DeviceContext.h"
#include "RenderBox.h"

extern const float width{ 800 }, height{ 600 };

typedef struct { float m[4][4]; } matrix_t;

extern const float PI = 3.14159265;

int main(void)
{
	char *title = "Fox3D";

	Screen screen;

	if (screen.init(width, height, title))
		return -1;

	Device device(screen.m_fb, width, height);

	RenderBox renderBox(&device);

	while (screen.m_exit == 0 && screen.m_keys[VK_ESCAPE] == 0) {
		screen.dispatch();
		device.clear();

		renderBox.update();
		renderBox.render();

		screen.update();
		//Sleep(1); // commented for Debug
	}

	renderBox.clear();

	return 0;
}
