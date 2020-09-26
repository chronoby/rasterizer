#pragma once

#include <algorithm>
#include "triangle.h"

class rasterizer
{
public:
	rasterizer(int width, int height);

	void set_model(const Matrix4f& m);
	void set_voiw(const Matrix4f& v);
	void set_projection(const Matrix4f& p);



private:


};