#pragma once

#include <windows.h>

#ifdef _MSC_VER
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#endif

class Screen {
public:
	static int m_exit;
	unsigned char *m_fb = NULL;	
	static int m_keys[512];	

public:
	int init(int w, int h, const char *title);	
	void dispatch(void);							
	void update(void);							

private:
	int m_w, m_h;
	int m_mx = 0, m_my = 0, m_mb = 0;
	HWND m_handle = NULL;		  
	HDC m_dc = NULL;		         
	HBITMAP m_hb = NULL;	         
	HBITMAP m_ob = NULL;	
	long m_pitch = 0;

private:
	int close(void);							

};
