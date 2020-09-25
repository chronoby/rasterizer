#include "util.h"
Vector3f& Vector3f::operator=(Vector3f temp)
{
	val[0] = temp[0];
	val[1] = temp[1];
	val[2] = temp[2];
}

Vector4f& Vector4f::operator=(Vector4f temp)
{
	val[0] = temp[0];
	val[1] = temp[1];
	val[2] = temp[2];
	val[3] = temp[3];
}