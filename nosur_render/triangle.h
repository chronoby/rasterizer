#pragma once

#include "util.h"
class triangle
{
public:
	triangle() = default;
	void setVertex(int index, Vector3f ver);
	void setColor(int index, float r, float g, float b);
	void setNormal(int index, Vector3f n);
private:
	Vector3f pos[3];
	Vector3f color[3];
	Vector3f normal[3];
};
