#include "util.h"
Vector3f& Vector3f::operator=(Vector3f temp)
{
	for (int i = 0; i < 3; ++i)
		val[i] = temp[i];
	return *this;
}

Vector4f& Vector4f::operator=(Vector4f temp)
{
	for (int i = 0; i < 4; ++i)
		val[i] = temp[i];
	return *this;
}

Matrix4f::Matrix4f()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			val[i][j] = 0;
}