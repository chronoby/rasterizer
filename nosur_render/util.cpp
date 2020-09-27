#include "util.h"

Mymath::Vector3i& Mymath::Vector3i::operator=(Mymath::Vector3i temp)
{
	for (int i = 0; i < 3; ++i)
		val[i] = temp[i];
	return *this;
}

Mymath::Vector3f& Mymath::Vector3f::operator=(Mymath::Vector3f temp)
{
	for (int i = 0; i < 3; ++i)
		val[i] = temp[i];
	return *this;
}

Mymath::Vector4f& Mymath::Vector4f::operator=(Mymath::Vector4f temp)
{
	for (int i = 0; i < 4; ++i)
		val[i] = temp[i];
	return *this;
}

Mymath::Matrix4f::Matrix4f()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			val[i][j] = 0;
}

Mymath::Matrix4f::Matrix4f(float v[])
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			val[i][j] = v[i * 4 + j];
}