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

Mymath::Matrix4f::Matrix4f(float v[])
{
	val.resize(16);
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			val[i * 4 + j] = v[i * 4 + j];
}

std::vector<float>& Mymath::Matrix4f::operator[](std::size_t n)
{
	std::vector<float> res = { val[n * 4], val[n * 4 + 1], val[n * 4 + 2], val[n * 4 + 3] };
	return res;
}
const std::vector<float>& Mymath::Matrix4f::operator[](std::size_t n) const
{
	std::vector<float> res = { val[n * 4], val[n * 4 + 1], val[n * 4 + 2], val[n * 4 + 3] };
	return res;
}

Mymath::Matrix4f operator*(const Mymath::Matrix4f& lhs, const Mymath::Matrix4f& rhs)
{
	Mymath::Matrix4f res;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 4; ++k)
				;
}
