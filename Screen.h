#pragma once

#include <windows.h>

#ifdef _MSC_VER
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#endif

class Screen {
public:
	static int m_exit;
	unsigned char *m_fb = NULL;		// frame buffer
	static int m_keys[512];	// 当前键盘按下状态

public:
	int init(int w, int h, const char *title);	// 屏幕初始化
	void dispatch(void);							// 处理消息
	void update(void);							// 显示 FrameBuffer

private:
	int m_w, m_h;
	int m_mx = 0, m_my = 0, m_mb = 0;
	HWND m_handle = NULL;		// 主窗口 HWND          
	HDC m_dc = NULL;			// 配套的 HDC          
	HBITMAP m_hb = NULL;		// DIB                
	HBITMAP m_ob = NULL;		// 老的 BITMAP         
	long m_pitch = 0;

private:
	int close(void);								// 关闭屏幕

};
