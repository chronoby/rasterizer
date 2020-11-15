#include <stdexcept>
#include <array>
#include <algorithm>

#include "triangle.h"

void triangle::setVertex(int index, Mymath::Vector4f ver) { pos[index] = ver; }

void triangle::setNormal(int index, Mymath::Vector3f n) { normal[index] = n; }

void triangle::setColor(int index, float r, float g, float b)
{
    if ((r < 0.0) || (r > 255.) || (g < 0.0) || (g > 255.) || (b < 0.0) ||
        (b > 255.)) 
    {
        throw std::runtime_error("Invalid color values");
    }

    color[index] = Mymath::Vector3f(r, g, b);
}

void triangle::setTexCoord(int ind, Mymath::Vector2f uv)
{
    tex_coords[ind] = uv;
}

std::vector<Mymath::Vector4f> triangle::toVector4() const
{
    std::vector<Mymath::Vector4f> res;
    Mymath::Vector4f vec;
    for (int i = 0; i < 3; ++i)
    {
        vec = pos[i];
        res.push_back(Mymath::Vector4f(vec.x(), vec.y(), vec.z(), 1.0f));
    }
    return res;
}
