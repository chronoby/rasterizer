#include <stdexcept>

#include "triangle.h"

void triangle::setVertex(int index, Vector3f ver) { pos[index] = ver; }

void triangle::setNormal(int index, Vector3f n) { normal[index] = n; }

void triangle::setColor(int index, float r, float g, float b)
{
    if ((r < 0.0) || (r > 255.) || (g < 0.0) || (g > 255.) || (b < 0.0) ||
        (b > 255.)) {
        throw std::runtime_error("Invalid color values");
    }

    color[index] = Vector3f((float)r / 255., (float)g / 255., (float)b / 255.);
    return;
}