#pragma once

#include <vector>
#include <cstdlib>

constexpr float MY_PI = 3.1415926f;

namespace Mymath 
{
	template <class T, int size>
	class Vector
	{
	public:
		Vector() : val(size) { }
		Vector(T v1, T v2);
		Vector(T v1, T v2, T v3);
		Vector(T v1, T v2, T v3, T v4);
		Vector(T v[]);

		Vector& operator=(Vector temp);
		T& operator[](std::size_t n) { return val[n]; }
		const T& operator[](std::size_t n) const { return val[n]; }
		const Vector operator/(const T temp);

		inline T x() const { return val[0]; }
		inline T y() const { return val[1]; }
		inline T z() const { return size >= 3 ? val[2] : 0; }
		inline T w() const { return size >= 4 ? val[3] : 0; }

	private:
		std::vector<T> val;
	};

	template <class T, int size>
	class Matrix
	{
	public:
		Matrix() : val(size* size) {  }
		Matrix(T v[]);
		std::vector<T> operator[](std::size_t n);
		const std::vector<T> operator[](std::size_t n) const;

		friend Matrix operator*(const Matrix& lhs, const Matrix& rhs)
		{
			Matrix<T, size> res;
			for (int i = 0; i < size; ++i)
				for (int j = 0; j < size; ++j)
					for (int k = 0; k < size; ++k)
						res.val[i * size + j] += lhs.val[i * size + k] * rhs.val[k * size + j];
			return res;
		}
		Vector<T, size> operator*(const Vector<T, size>& rhs);

	private:
		std::vector<float> val;
	};

	using Vector3f = Vector<float, 3>;
	using Vector3i = Vector<int, 3>;
	using Vector3c = Vector<unsigned int, 3>;
	using Vector4f = Vector<float, 4>;
	using Matrix4f = Matrix<float, 4>;

	template <class T, int size>
	Vector<T, size>::Vector(T v[])
	{
		val.resize(size);
		for (int i = 0; i < size; ++i)
			val[i] = v[i];
	}
	template <class T, int size>
	Vector<T, size>::Vector(T v1, T v2)
	{
		val.push_back(v1);
		val.push_back(v2);
	}

	template <class T, int size>
	Vector<T, size>::Vector(T v1, T v2, T v3)
	{
		val.push_back(v1);
		val.push_back(v2);
		val.push_back(v3);
	}

	template <class T, int size>
	Vector<T, size>::Vector(T v1, T v2, T v3, T v4)
	{
		val.push_back(v1);
		val.push_back(v2);
		val.push_back(v3);
		val.push_back(v4);
	}

	template <class T, int size>
	Vector<T, size>& Vector<T, size>::operator=(Vector<T, size> temp)
	{
		val = temp.val;
		return *this;
	}

	template <class T, int size>
	const Vector<T, size> Vector<T, size>::operator/(const T temp)
	{
		T v[size];
		for (int i = 0; i < size; ++i)
			v[i] = val[i] / temp;
		Vector<T, size> res(v);
		return res;
	}

	template <class T, int size>
	Matrix<T, size>::Matrix(T v[])
	{
		for (int i = 0; i < size * size; ++i)
			val.push_back(v[i]);
	}

	template <class T, int size>
	std::vector<T> Matrix<T, size>::operator[](std::size_t n)
	{
		std::vector<float> res;
		for (int i = 0; i < size; ++i)
			res.push_back(val[n * size + i]);
		return res;
	}

	template <class T, int size>
	const std::vector<T> Matrix<T, size>::operator[](std::size_t n) const
	{
		std::vector<float> res;
		for (int i = 0; i < size; ++i)
			res.push_back(val[n * size + i]);
		return res;
	}

	template <class T, int size>
	Vector<T, size> Matrix<T, size>::operator*(const Vector<T, size>& rhs)
	{
		Vector<T, size> res;
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
				res[i] += val[i * size + j] * rhs[j];
		return res;
	}
		
}


