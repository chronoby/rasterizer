#pragma once

#include "util.h"
class triangle
{
public:
	triangle() = default;
	void setVertex(int index, Mymath::Vector3f ver);
	void setColor(int index, float r, float g, float b);
	void setNormal(int index, Mymath::Vector3f n);
	std::vector<Mymath::Vector4f> toVector4() const;
	const Mymath::Vector3f getColor() const { return color[0] * 255.0; }

	Mymath::Vector3f pos[3];

private:
	Mymath::Vector3f color[3];
	Mymath::Vector3f normal[3];
};
