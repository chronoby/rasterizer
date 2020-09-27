#include "rasterizer.h"

rst::rasterizer::rasterizer(int w, int h)
{
	frame_buff.resize(width * w);
	z_buff.resize(width * h);
	width = w;
	height = h;
}