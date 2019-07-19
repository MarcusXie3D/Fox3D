#include "Screen.h"

int Screen::m_exit = 0;
int Screen::m_keys[512];

static LRESULT events(HWND, UINT, WPARAM, LPARAM);

// 初始化窗口并设置标题
int Screen::init(int w, int h, const char *title) {
	WNDCLASSA wc = { CS_BYTEALIGNCLIENT, (WNDPROC)events, 0, 0, 0,
		NULL, NULL, NULL, NULL, "SCREEN3.1415926" };
	BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB,
		w * h * 4, 0, 0, 0, 0 } };
	RECT rect = { 0, 0, w, h };
	int wx, wy, sx, sy;
	LPVOID ptr;
	HDC hDC;

	close();

	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	if (!RegisterClassA(&wc)) return -1;

	m_handle = CreateWindowA("SCREEN3.1415926", title,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
	if (m_handle == NULL) return -2;

	m_exit = 0;
	hDC = GetDC(m_handle);
	m_dc = CreateCompatibleDC(hDC);
	ReleaseDC(m_handle, hDC);

	m_hb = CreateDIBSection(m_dc, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
	if (m_hb == NULL) return -3;

	m_ob = (HBITMAP)SelectObject(m_dc, m_hb);
	m_fb = (unsigned char*)ptr;
	m_w = w;
	m_h = h;
	m_pitch = w * 4;

	AdjustWindowRect(&rect, GetWindowLong(m_handle, GWL_STYLE), 0);
	wx = rect.right - rect.left;
	wy = rect.bottom - rect.top;
	sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
	sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
	if (sy < 0) sy = 0;
	SetWindowPos(m_handle, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
	SetForegroundWindow(m_handle);

	ShowWindow(m_handle, SW_NORMAL);
	dispatch();

	memset(m_keys, 0, sizeof(int) * 512);
	memset(m_fb, 0, w * h * 4);

	return 0;
}

int Screen::close(void) {
	if (m_dc) {
		if (m_ob) {
			SelectObject(m_dc, m_ob);
			m_ob = NULL;
		}
		DeleteDC(m_dc);
		m_dc = NULL;
	}
	if (m_hb) {
		DeleteObject(m_hb);
		m_hb = NULL;
	}
	if (m_handle) {
		CloseWindow(m_handle);
		m_handle = NULL;
	}
	return 0;
}

static LRESULT events(HWND hWnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {
	static BOOL fDraw = FALSE;
	switch (msg) {
	case WM_CLOSE: Screen::m_exit = 1; break;
	case WM_KEYDOWN: Screen::m_keys[wParam & 511] = 1; break;
	case WM_KEYUP: Screen::m_keys[wParam & 511] = 0; break;

	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

void Screen::dispatch(void) {
	MSG msg;
	while (1) {
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;
		if (!GetMessage(&msg, NULL, 0, 0)) break;
		DispatchMessage(&msg);
	}
}

void Screen::update(void) {
	HDC hDC = GetDC(m_handle);
	BitBlt(hDC, 0, 0, m_w, m_h, m_dc, 0, 0, SRCCOPY);
	ReleaseDC(m_handle, hDC);
	dispatch();
}
