#include <iostream>
#include <cstdlib>

#include "util.h"
#include "pipeline.h"
#include "RWindow.h"
#include "transform.h"


int main(int argc, char* argv[])
{
    rst::rasterizer r(700, 700);

    Mymath::Vector3f eye_pos = { 0,0,5 };
    float angle = 0;

    std::vector<Mymath::Vector3f> pos
    {
            {2, 0, -2},
            {0, 2, -2},
            {-2, 0, -2},
            {3.5, -1, -5},
            {2.5, 1.5, -5},
            {-1, 0.5, -5}
    };

    std::vector<Mymath::Vector3i> ind
    {
            {0, 1, 2},
            {3, 4, 5}
    };

    std::vector<Mymath::Vector3f> cols
    {
            {217.0, 238.0, 185.0},
            {217.0, 238.0, 185.0},
            {217.0, 238.0, 185.0},
            {185.0, 217.0, 238.0},
            {185.0, 217.0, 238.0},
            {185.0, 217.0, 238.0}
    };

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);
    auto col_id = r.load_colors(cols);

    //r.clear();

    r.set_model(get_model_matrix(angle));
    r.set_view(get_view_matrix(eye_pos));
    r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

    r.draw(pos_id, ind_id, col_id, rst::Primitive::Triangle);

    HINSTANCE hIns = ::GetModuleHandle(0);
    RWindow RWin(hIns);

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
