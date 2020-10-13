#include <tuple>
#include <cmath>
#include <algorithm>

#include "rasterizer.h"

rst::rasterizer::rasterizer(int w, int h)
{
	frame_buff.resize(w * h);
	z_buff.resize(w * h);
	width = w;
	height = h;
}

rst::pos_buf_id rst::rasterizer::load_positions(const std::vector<Mymath::Vector3f>& positions)
{
	auto id = get_next_id();
	pos_buf.emplace(id, positions);
	return { id };
}

rst::ind_buf_id rst::rasterizer::load_indices(const std::vector<Mymath::Vector3i>& indices)
{
	auto id = get_next_id();
	ind_buf.emplace(id, indices);
	return { id };
}

rst::col_buf_id rst::rasterizer::load_colors(const std::vector<Mymath::Vector3f>& colors)
{
	auto id = get_next_id();
	col_buf.emplace(id, colors);
	return { id };
}

Mymath::Vector4f to_vec4(const Mymath::Vector3f& v3, float w = 1.0f)
{
	return Mymath::Vector4f(v3[0], v3[1], v3[2], w);
}

float side(int ptx, int pty, Mymath::Vector3f p1, Mymath::Vector3f p2)
{
	return (p2.x() - p1.x()) * ((float)pty - p1.y()) - (p2.y() - p1.y()) * ((float)ptx - p1.x());
}

static bool insideTriangle(int x, int y, const Mymath::Vector3f* _v)
{
	float side1 = side(x, y, _v[0], _v[1]);
	float side2 = side(x, y, _v[1], _v[2]);
	float side3 = side(x, y, _v[2], _v[0]);
	return ((side1 < 0) && (side2 < 0) && (side3 < 0)) || ((side1 > 0) && (side2 > 0) && (side3 > 0));
}

static std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Mymath::Vector3f* v)
{
	float c1 = (x * (v[1].y() - v[2].y()) + (v[2].x() - v[1].x()) * y + v[1].x() * v[2].y() - v[2].x() * v[1].y()) / (v[0].x() * (v[1].y() - v[2].y()) + (v[2].x() - v[1].x()) * v[0].y() + v[1].x() * v[2].y() - v[2].x() * v[1].y());
	float c2 = (x * (v[2].y() - v[0].y()) + (v[0].x() - v[2].x()) * y + v[2].x() * v[0].y() - v[0].x() * v[2].y()) / (v[1].x() * (v[2].y() - v[0].y()) + (v[0].x() - v[2].x()) * v[1].y() + v[2].x() * v[0].y() - v[0].x() * v[2].y());
	float c3 = (x * (v[0].y() - v[1].y()) + (v[1].x() - v[0].x()) * y + v[0].x() * v[1].y() - v[1].x() * v[0].y()) / (v[2].x() * (v[0].y() - v[1].y()) + (v[1].x() - v[0].x()) * v[2].y() + v[0].x() * v[1].y() - v[1].x() * v[0].y());
	return std::tuple<float, float, float>{ c1, c2, c3 };
}

void rst::rasterizer::draw(pos_buf_id pos_buffer, ind_buf_id ind_buffer, col_buf_id col_buffer, Primitive type)
{
	std::vector<Mymath::Vector3f>& buf = pos_buf[pos_buffer.pos_id];
	std::vector<Mymath::Vector3i>& ind = ind_buf[ind_buffer.ind_id];
	std::vector<Mymath::Vector3f>& col = col_buf[col_buffer.col_id];
	
	float f1 = (50 - 0.1) / 2.0;
	float f2 = (50 + 0.1) / 2.0;

	Mymath::Matrix4f mvp = projection * view * model;
	for (auto& i : ind)
	{
		triangle t;
		Mymath::Vector4f v[] =
		{
			mvp * to_vec4(buf[i[0]], 1.0f),
			mvp * to_vec4(buf[i[1]], 1.0f),
			mvp * to_vec4(buf[i[2]], 1.0f)
		};
		// Homogeneous division
		for (auto& vec : v)
			vec = vec / vec.w();
		// Viewport transformation
		for (auto& vert : v)
		{
			vert[0] = 0.5 * width * (vert[0] + 1.0);
			vert[1] = 0.5 * height * (vert[1] + 1.0);
			vert[2] = vert[2] * f1 + f2;
		}
		for (int i = 0; i < 3; ++i)
		{
			t.setVertex(i, v[i].head3());
			t.setVertex(i, v[i].head3());
			t.setVertex(i, v[i].head3());
		}

		auto col_x = col[i[0]];
		auto col_y = col[i[1]];
		auto col_z = col[i[2]];

		t.setColor(0, col_x[0], col_x[1], col_x[2]);
		t.setColor(1, col_y[0], col_y[1], col_y[2]);
		t.setColor(2, col_z[0], col_z[1], col_z[2]);

		rasterize_triangle(t);
	}
}

void rst::rasterizer::set_pixel(const Mymath::Vector3i& point, const Mymath::Vector3f& color)
{
	int index = get_index(point.x(), point.y());
	frame_buff[index] = color;
}

void rst::rasterizer::rasterize_triangle(const triangle& t)
{
	auto v = t.toVector4();

	int bounding_l = floor(std::min(t.pos[0].x(), std::min(t.pos[1].x(), t.pos[2].x())));
	int bounding_r = ceil(std::max(t.pos[0].x(), std::max(t.pos[1].x(), t.pos[2].x())));
	int bounding_u = ceil(std::max(t.pos[0].y(), std::max(t.pos[1].y(), t.pos[2].y())));
	int bounding_d = floor(std::max(t.pos[0].y(), std::max(t.pos[1].y(), t.pos[2].y())));

	for (int i = bounding_l; i <= bounding_r; ++i)
	{
		for (int j = bounding_d; j <= bounding_u; ++j)
		{
			auto Barycentric = computeBarycentric2D(i, j, t.pos);
			float alpha = std::get<0>(Barycentric);
			float beta = std::get<1>(Barycentric);
			float gamma = std::get<2>(Barycentric);
			float w_reciprocal = 1.0 / (alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
			float z_interpolated = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
			z_interpolated *= w_reciprocal;

			// if current pixel should be painted, draw it using the color of the triangle t
			if (z_interpolated < z_buff[get_index(i, j)]) {
				Mymath::Vector3i current_pixel = { i, j, 0 };
				set_pixel(current_pixel, t.getColor());
			}
		}
	}
}