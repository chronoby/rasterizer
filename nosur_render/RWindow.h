#pragma once

#include <windows.h>

#include "rasterizer.h"

// window class
class RWindow
{
public:
    RWindow(HINSTANCE h) : hIns(h) { }
    RWindow(HINSTANCE h, rst::rasterizer rt) : hIns(h), r(rt) {  }
    BOOL InitApplication();
    BOOL InitInstance();
    static LRESULT CALLBACK __WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
    HINSTANCE hIns;
    int x = 400, y = 300;
    rst::rasterizer r;
};
