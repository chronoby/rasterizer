#pragma once

#include <vector>
#include <cstdlib>

constexpr float MY_PI = 3.1415926;

namespace Mymath 
{
	class Vector3i
	{
	public:
		Vector3i() :val(3, 0) { }
		Vector3i(int a, int b, int c) { val.resize(3); val[0] = a; val[1] = b; val[2] = c; }
		Vector3i& operator=(Vector3i temp);
		int& operator[](std::size_t n) { return val[n]; }
		const int& operator[](std::size_t n) const { return val[n]; }
	private:
		std::vector<int> val;
	};

	class Vector3f
	{
	public:
		Vector3f() :val(3, 0.0f) { }
		Vector3f(float a, float b, float c) { val.resize(3); val[0] = a; val[1] = b; val[2] = c; }
		Vector3f& operator=(Vector3f temp);
		float& operator[](std::size_t n) { return val[n]; }
		const float& operator[](std::size_t n) const { return val[n]; }

	private:
		std::vector<float> val;
	};

	class Vector4f
	{
	public:
		Vector4f() :val(4, 0.0f) { }
		Vector4f(float a, float b, float c, float d) { val.resize(4); val[0] = a; val[1] = b; val[2] = c; val[3] = d; }
		float& operator[](std::size_t n) { return val[n]; }
		const float& operator[](std::size_t n) const { return val[n]; }
		Vector4f& operator=(Vector4f temp);
	private:
		std::vector<float> val;
	};

	class Matrix4f
	{
	public:
		Matrix4f() :val(16, 0.0f) { };
		Matrix4f(float v[]);
		std::vector<float>& operator[](std::size_t n);
		const std::vector<float>& operator[](std::size_t n) const;
		friend Matrix4f operator*(const Matrix4f& lhs, const Matrix4f& rhs);
	private:
		std::vector<float> val;
	};
}