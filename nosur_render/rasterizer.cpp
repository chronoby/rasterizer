#include "rasterizer.h"

rst::rasterizer::rasterizer(int w, int h)
{
	frame_buff.resize(w * h);
	z_buff.resize(w * h);
	width = w;
	height = h;
}