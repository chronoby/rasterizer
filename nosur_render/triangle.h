#pragma once

#include "util.h"
#include "texture.h"

class triangle
{
public:
	triangle() = default;
	void setVertex(int index, Mymath::Vector4f ver);
	void setColor(int index, float r, float g, float b);
	void setNormal(int index, Mymath::Vector3f n);
	void setTexCoord(int ind, Mymath::Vector2f uv);
	std::vector<Mymath::Vector4f> toVector4() const;

	Mymath::Vector4f pos[3];
	Mymath::Vector3f color[3];
	Mymath::Vector3f normal[3];
	Mymath::Vector2f tex_coords[3];

	texture* tex = nullptr;

};
