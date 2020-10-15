#include <stdexcept>
#include <array>
#include <algorithm>

#include "triangle.h"

void triangle::setVertex(int index, Mymath::Vector3f ver) { pos[index] = ver; }

void triangle::setNormal(int index, Mymath::Vector3f n) { normal[index] = n; }

void triangle::setColor(int index, unsigned char r, unsigned char g, unsigned char b)
{
    if ((r < 0.0) || (r > 255.) || (g < 0.0) || (g > 255.) || (b < 0.0) ||
        (b > 255.)) 
    {
        throw std::runtime_error("Invalid color values");
    }

    color[index] = Mymath::Vector3c(r, g, b);
}

std::vector<Mymath::Vector4f> triangle::toVector4() const
{
    std::vector<Mymath::Vector4f> res;
    Mymath::Vector3f vec;
    for (int i = 0; i < 3; ++i)
    {
        vec = pos[i];
        res.push_back(Mymath::Vector4f(vec.x(), vec.y(), vec.z(), 1.0f));
    }
    //std::transform(pos.begin(), pos.end(), res.begin(), [](auto& vec) {return Mymath::Vector4f(vec.x(), vec.y(), vec.z(), 1.0f); });
    return res;
}
