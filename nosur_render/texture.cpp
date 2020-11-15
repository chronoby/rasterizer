#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

texture::texture(const std::string& path)
{
	image_data = new unsigned char[3 * 1024 * 1024];
	image_data = stbi_load(path.c_str(), &width, &height, &channels_in_file, 0);
}

Mymath::Vector3f texture::getColor(int u, int v)
{
	auto pos = 3 * (u + v * height);
	return Mymath::Vector3f(static_cast<float>(image_data[pos]), 
		static_cast<float>(image_data[pos + 1]), static_cast<float>(image_data[pos + 2]));
}
