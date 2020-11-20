#pragma once

#include <cmath>
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
		Vector operator+(const Vector temp);
		Vector operator-(const Vector temp);
		Vector operator/(const T temp);

		template <class U>
		friend Vector<T, size> operator*(const Vector<T, size> lhs, const U rhs)
		{
			T v[size];
			for (int i = 0; i < size; ++i)
				v[i] = lhs.val[i] * rhs;
			Vector<T, size> res(v);
			return res;
		}
		T length() const;

		Vector normalized() const { return (*this) / this->length(); }

		T dot(Vector& rhs);

		Vector cwiseProduct(Vector rhs);

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
		Matrix<T, size> transpose();
		Matrix inverse();

	private:
		std::vector<float> val;

		void getCofactor(float A[size][size], float temp[size][size], int p, int q, int n);
		float determinant(float A[size][size], int n);
		void adjoint(float A[size][size], float adj[size][size]);
	};

	using Vector3f = Vector<float, 3>;
	using Vector3i = Vector<int, 3>;
	using Vector3c = Vector<unsigned int, 3>;
	using Vector4f = Vector<float, 4>;
	using Vector2f = Vector<float, 2>;
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
	Vector<T, size> Vector<T, size>::operator+(const Vector<T, size> temp)
	{
		T v[size];
		for (int i = 0; i < size; ++i)
			v[i] = val[i] + temp.val[i];
		Vector<T, size> res(v);
		return res;
	}

	template <class T, int size>	
	Vector<T, size> Vector<T, size>::operator-(const Vector<T, size> temp)
	{
		T v[size];
		for (int i = 0; i < size; ++i)
			v[i] = val[i] - temp.val[i];
		Vector<T, size> res(v);
		return res;
	}

	template <class T, int size>
	Vector<T, size> Vector<T, size>::operator/(const T temp)
	{
		T v[size];
		for (int i = 0; i < size; ++i)
			v[i] = val[i] / temp;
		Vector<T, size> res(v);
		return res;
	}

	template <class T, int size>
	Vector<T, size> operator/(const Vector<T, size> lhs, const T temp)
	{
		return lhs * (1 / temp);
	}

	template <class T, class U, int size>
	Vector<T, size> operator*(const U lhs, const Vector<T, size> rhs)
	{
		return rhs * lhs;
	}

	template <class T, int size>
	T Vector<T, size>::length() const
	{
		T length_Square = 0;
		for (int i = 0; i < size; ++i)
			length_Square += val[i] * val[i];
		return sqrt(length_Square);
	}

	template <class T, int size>
	T Vector<T, size>::dot(Vector<T, size>& rhs)
	{
		T res = 0;
		for (int i = 0; i < size; ++i)
			res += val[i] * rhs.val[i];
		return res;
	}

	template <class T, int size>
	Vector<T, size> Vector<T, size>::cwiseProduct(Vector<T, size> rhs)
	{
		T v[size];
		for (int i = 0; i < size; ++i)
			v[i] = val[i] * rhs[i];
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

	template <class T, int size>
	Matrix<T, size> Matrix<T, size>::transpose()
	{
		T data[size * size];
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
				data[i * size + j] = val[j * size + i];
		Matrix<T, size> res(data);
		return res;
	}

	template <class T, int size>
	Matrix<T, size> Matrix<T, size>::inverse()
	{
		float A[size][size];
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
				A[i][j] = val[i * size + j];

		float det = determinant(A, size);
		if (det == 0)
		{
			Matrix<T, size> zero;
			return zero;
		}

		float adj[size][size];
		adjoint(A, adj);
		float inverse[size * size];
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				inverse[i * size + j] = adj[i][j] / float(det);
		Matrix<T, size> res(inverse);
		return res;
	}

	template <class T, int size>
	void Matrix<T, size>::adjoint(float A[size][size], float adj[size][size])
	{
		if (size == 1)
		{
			adj[0][0] = 1;
			return;
		}
		int sign = 1;
		float temp[size][size];

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				getCofactor(A, temp, i, j, size);
				sign = ((i + j) % 2 == 0) ? 1 : -1;

				adj[j][i] = (sign) * (determinant(temp, size - 1));
			}
		}
	}

	template <class T, int size>
	void Matrix<T, size>::getCofactor(float A[size][size], float temp[size][size], int p, int q, int n)
	{
		int i = 0, j = 0;

		for (int row = 0; row < n; row++)
		{
			for (int col = 0; col < n; col++)
			{
				if (row != p && col != q)
				{
					temp[i][j++] = A[row][col];

					if (j == n - 1)
					{
						j = 0;
						i++;
					}
				}
			}
		}
	}

	template <class T, int size>
	float Matrix<T, size>::determinant(float A[size][size], int n)
	{
		float D = 0;
		if (n == 1)
			return A[0][0];

		float temp[size][size];
		int sign = 1;
		for (int f = 0; f < n; f++)
		{
			getCofactor(A, temp, 0, f, n);
			D += sign * A[0][f] * determinant(temp, n - 1);
			sign = -sign;
		}

		return D;
	}
}
