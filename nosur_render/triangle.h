#pragma once

#include "util.h"
class triangle
{
public:
	triangle() = default;
	void setVertex(int index, Mymath::Vector3f ver);
	void setColor(int index, unsigned char r, unsigned char g, unsigned char b);
	void setNormal(int index, Mymath::Vector3f n);
	std::vector<Mymath::Vector4f> toVector4() const;
	Mymath::Vector3c getColor() const { return color[0]; }

	Mymath::Vector3f pos[3];

private:
	Mymath::Vector3c color[3];
	Mymath::Vector3f normal[3];
};
