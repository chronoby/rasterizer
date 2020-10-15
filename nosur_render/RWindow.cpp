#include "RWindow.h"

rst::rasterizer RWindow::r;
const int RWindow::w;
const int RWindow::h;

BOOL RWindow::InitApplication()
{
    WNDCLASSEX wc;
    LPCWSTR szClass = TEXT("myRenderer");
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = __WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hIns;
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClass;
    wc.hIconSm = NULL;

    if (!RegisterClassEx(&wc)) exit(0);
    return TRUE;
}

BOOL RWindow::InitInstance()
{
    DWORD style = WS_OVERLAPPEDWINDOW;
    DWORD styleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    LPCWSTR szClass = TEXT("myRenderer");
    LPCWSTR szTitle = TEXT("Renderer");

    RECT rect = { 0, 0, 800, 600 };
    AdjustWindowRectEx(&rect, style, false, styleEx);

    HWND hWnd = CreateWindowEx(styleEx, szClass, szTitle, style, 0, 0,
        rect.right - rect.left, rect.bottom - rect.top, 0, 0, hIns, 0);
    if (hWnd == 0) exit(0);

    UpdateWindow(hWnd);
    ShowWindow(hWnd, SW_SHOW);

    return TRUE;
}

LRESULT CALLBACK RWindow::__WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    std::vector<Mymath::Vector3c> frame;

    BITMAPINFO info;
    ZeroMemory(&info, sizeof(BITMAPINFO));
    info.bmiHeader.biBitCount = 24;
    info.bmiHeader.biWidth = w;
    info.bmiHeader.biHeight = h;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biSizeImage = 0;
    info.bmiHeader.biCompression = BI_RGB;

    unsigned char* buff = r.buff;


    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
//        for(int j = 0; j < 700; ++j)
//            for (int i = 0; i < 700; ++i)
//            {
//                int index = j * 700 + i;
//                SetPixel(hdc, i, j, RGB(frame[index][0], frame[index][1], frame[index][2]));
//            }
        frame = r.frame_buffer();
        SetDIBitsToDevice(hdc, 0, 0, w, h, 0, 0, 0, h, buff, &info, DIB_RGB_COLORS);
        EndPaint(hWnd, &ps);
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:     //°´Esc¼üÍË³ö³ÌÐò
            PostQuitMessage(0);
            break;
        case 0x41:
            // todo
            break;
        case 0x44:
            break;
        }
        InvalidateRect(hWnd, NULL, TRUE);
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}