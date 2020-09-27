#include <iostream>
#include <cstdlib>

#include "util.h"
#include "pipeline.h"
#include "RWindow.h"


int main(int argc, char* argv[])
{
    HINSTANCE hIns = ::GetModuleHandle(0);
    RWindow RWin(hIns);

    rst::rasterizer r(700, 700);

    if (RWin.InitApplication() == FALSE)
        return FALSE;
    if (RWin.InitInstance() == FALSE)
        return FALSE;

    MSG msg = { 0 };
    while (msg.message != WM_QUIT) 
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else 
        {
            //TODO, do this
        }
    }

    return 0;
}
