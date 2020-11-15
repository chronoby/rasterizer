#include <iostream>
#include <cstdlib>

#include "util.h"
#include "RWindow.h"
#include "transform.h"
#include "shader.h"
#include "OBJ_Loader.h"

int main(int argc, char* argv[])
{
    std::vector<triangle*> triangle_list;

    float angle = 140.0;
    std::string obj_path = "../models/spot/";
    objl::Loader loader;
    bool load_res = loader.LoadFile("../models/spot/spot_triangulated_good.obj");
    if (load_res == false)
        std::cout << "Load obj error!" << std::endl;
    else
        std::cout << "Load obj success" << std::endl;
    int count = 1;
    for (auto mesh : loader.LoadedMeshes)
    {
        for (int i = 0; i < mesh.Vertices.size(); i += 3)
        {
            triangle* t = new triangle;
            for (int j = 0; j < 3; ++j)
            {
                t->setVertex(j, Mymath::Vector4f(mesh.Vertices[i + j].Position.X, mesh.Vertices[i + j].Position.Y, 
                    mesh.Vertices[i + j].Position.Z, 1.0));
                t->setNormal(j, Mymath::Vector3f(mesh.Vertices[i + j].Normal.X, mesh.Vertices[i + j].Normal.Y, mesh.Vertices[i + j].Normal.Z));
                t->setTexCoord(j, Mymath::Vector2f(mesh.Vertices[i + j].TextureCoordinate.X, mesh.Vertices[i + j].TextureCoordinate.Y));
            }
            triangle_list.push_back(t);
            std::cout << "Triangle " << count++ << " / " << mesh.Vertices.size() / 3  << " loaded." << std::endl;
        }
    }

    rst::rasterizer r(700, 700);
    auto texture_path = "spot_texture.png";
    r.set_texture(texture(obj_path + texture_path));

    std::function<Mymath::Vector3f(fragment_shader_payload&)> active_shader = normal_fragment_shader;
    Mymath::Vector3f eye_pos = { 0, 0, 10 };
    r.set_vertex_shader(vertex_shader);
    r.set_fragment_shader(active_shader);

    r.clear();

    r.set_model(get_model_matrix(angle));
    r.set_view(get_view_matrix(eye_pos));
    r.set_projection(get_projection_matrix(45.0f, 1.0f, 0.1f, 50.f));
    r.draw(triangle_list);

    HINSTANCE hIns = ::GetModuleHandle(0);
    RWindow RWin(hIns, r);

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
        else {  }
    }

    return 0;
}
