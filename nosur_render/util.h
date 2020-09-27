#pragma once

#include <cstdlib>

constexpr float MY_PI = 3.1415926;

namespace Mymath 
{
	class Vector3i
	{
	public:
		Vector3i() { val[0] = val[1] = val[2] = 0.0f; }
		Vector3i(float a, float b, float c) { val[0] = a; val[1] = b; val[2] = c; }
		Vector3i& operator=(Vector3i temp);
		float& operator[](std::size_t n) { return val[n]; }
		const float& operator[](std::size_t n) const { return val[n]; }

	private:
		float val[3];
	};

	class Vector3f
	{
	public:
		Vector3f() { val[0] = val[1] = val[2] = 0.0f; }
		Vector3f(float a, float b, float c) { val[0] = a; val[1] = b; val[2] = c; }
		Vector3f& operator=(Vector3f temp);
		float& operator[](std::size_t n) { return val[n]; }
		const float& operator[](std::size_t n) const { return val[n]; }

	private:
		float val[3];
	};

	class Vector4f
	{
	public:
		Vector4f() { val[0] = val[1] = val[2] = val[3] = 0; }
		Vector4f(float a, float b, float c, float d) { val[0] = a; val[1] = b; val[2] = c; val[3] = d; }
		float& operator[](std::size_t n) { return val[n]; }
		const float& operator[](std::size_t n) const { return val[n]; }
		Vector4f& operator=(Vector4f temp);
	private:
		float val[4];
	};

	class Matrix4f
	{
	public:
		Matrix4f();
		Matrix4f(float v[]);

	private:
		float val[4][4];
	};
}