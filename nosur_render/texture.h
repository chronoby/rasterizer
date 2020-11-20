#pragma once

#include <string>
#include "util.h"

class texture
{
public:
	texture() = default;
	texture(const std::string& path);

	Mymath::Vector3f getColor(float u, float v);

private:
	unsigned char* image_data;
	int width;
	int height;
	int channels_in_file;
};