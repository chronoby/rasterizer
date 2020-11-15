#include <tuple>
#include <cmath>
#include <array>
#include <algorithm>
#include <iostream>

#include "rasterizer.h"

rst::rasterizer::rasterizer(int w, int h): width(w), height(h)
{
	frame_buff.resize(w * h);
	z_buff.resize(w * h);
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

float side(int ptx, int pty, Mymath::Vector4f p1, Mymath::Vector4f p2)
{
	return (p2.x() - p1.x()) * ((float)pty - p1.y()) - (p2.y() - p1.y()) * ((float)ptx - p1.x());
}

static bool insideTriangle(int x, int y, const Mymath::Vector4f* _v)
{
	float side1 = side(x, y, _v[0], _v[1]);
	float side2 = side(x, y, _v[1], _v[2]);
	float side3 = side(x, y, _v[2], _v[0]);
	return ((side1 < 0) && (side2 < 0) && (side3 < 0)) || ((side1 > 0) && (side2 > 0) && (side3 > 0));
}

static std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Mymath::Vector4f* v)
{
	float c1 = (x * (v[1].y() - v[2].y()) + (v[2].x() - v[1].x()) * y + v[1].x() * v[2].y() - v[2].x() * v[1].y()) / (v[0].x() * (v[1].y() - v[2].y()) + (v[2].x() - v[1].x()) * v[0].y() + v[1].x() * v[2].y() - v[2].x() * v[1].y());
	float c2 = (x * (v[2].y() - v[0].y()) + (v[0].x() - v[2].x()) * y + v[2].x() * v[0].y() - v[0].x() * v[2].y()) / (v[1].x() * (v[2].y() - v[0].y()) + (v[0].x() - v[2].x()) * v[1].y() + v[2].x() * v[0].y() - v[0].x() * v[2].y());
	float c3 = (x * (v[0].y() - v[1].y()) + (v[1].x() - v[0].x()) * y + v[0].x() * v[1].y() - v[1].x() * v[0].y()) / (v[2].x() * (v[0].y() - v[1].y()) + (v[1].x() - v[0].x()) * v[2].y() + v[0].x() * v[1].y() - v[1].x() * v[0].y());
	return std::tuple<float, float, float>{ c1, c2, c3 };
}

void rst::rasterizer::draw(std::vector<triangle*>& triangle_list)
{
	float f1 = (50.f - 0.1f) / 2.0f;
	float f2 = (50.f + 0.1f) / 2.0f;

	Mymath::Matrix4f mvp = projection * view * model;
	int count = 1;
	for (const auto& t: triangle_list)
	{
		triangle newtri = *t;
		std::array<Mymath::Vector4f, 3> mm
		{
			(view * model * t->pos[0]),
			(view * model * t->pos[1]),
			(view * model * t->pos[2])
		};

		std::array<Mymath::Vector3f, 3> viewspace_pos
		{
			(Mymath::Vector3f(mm[0].x(), mm[0].y(), mm[0].z())),
			(Mymath::Vector3f(mm[1].x(), mm[1].y(), mm[1].z())),
			(Mymath::Vector3f(mm[2].x(), mm[2].y(), mm[2].z()))
		};

		Mymath::Vector4f v[] =
		{
			mvp * t->pos[0],
			mvp * t->pos[1],
			mvp * t->pos[2]
		};
		// Homogeneous division
		for (auto& vec : v)
			vec = vec / vec.w();

		Mymath::Matrix4f inv_trans = (view * model).inverse().transpose();
		Mymath::Vector4f n[] =
		{
			inv_trans * to_vec4(t->normal[0], 0.0f),
			inv_trans * to_vec4(t->normal[1], 0.0f),
			inv_trans * to_vec4(t->normal[2], 0.0f)
		};

		// Viewport transformation
		for (auto& vert : v)
		{
			vert[0] = 0.5f * width * (vert[0] + 1.0);
			vert[1] = 0.5f * height * (vert[1] + 1.0);
			vert[2] = vert[2] * f1 + f2;
		}

		for (int i = 0; i < 3; ++i)
		{
<<<<<<< HEAD
			newtri.setVertex(i, v[i]);
=======
			Mymath::Vector3f vert3(v[i].x(), v[i].y(), v[i].z());
			t.setVertex(i, vert3);
			t.setVertex(i, vert3);
			t.setVertex(i, vert3);
>>>>>>> a1dc0bb00f406bc20f2b3af3b7f97b20bf5f37d4
		}

		for (int i = 0; i < 3; ++i)
		{
			newtri.setNormal(i, Mymath::Vector3f(n[i].x(), n[i].y(), n[i].z()));
		}

		newtri.setColor(0, 148, 121, 92);
		newtri.setColor(1, 148, 121, 92);
		newtri.setColor(2, 148, 121, 92);
		
		rasterize_triangle(newtri, viewspace_pos);
		std::cout << "Triangle " << count++ << " / " << triangle_list.size() << " rendered." << std::endl;
	}
}

void rst::rasterizer::set_frame(const Mymath::Vector3i& point, const Mymath::Vector3f& color)
{
	int index = get_index(point.x(), point.y());
	frame_buff[index] = color;
}

void rst::rasterizer::clear()
{
	std::fill(frame_buff.begin(), frame_buff.end(), Mymath::Vector3f{ 0, 0, 0 });

	std::fill(z_buff.begin(), z_buff.end(), std::numeric_limits<float>::infinity());
}

void rst::rasterizer::rasterize_triangle(const triangle& t, const std::array<Mymath::Vector3f, 3>& world_pos)
{
	auto v = t.toVector4();

	int bounding_l = (int)floor(std::min(t.pos[0].x(), std::min(t.pos[1].x(), t.pos[2].x())));
	int bounding_r = (int)ceil(std::max(t.pos[0].x(), std::max(t.pos[1].x(), t.pos[2].x())));
	int bounding_u = (int)ceil(std::max(t.pos[0].y(), std::max(t.pos[1].y(), t.pos[2].y())));
	int bounding_d = (int)floor(std::min(t.pos[0].y(), std::min(t.pos[1].y(), t.pos[2].y())));

	for (int i = bounding_l; i <= bounding_r; ++i)
	{
		for (int j = bounding_d; j <= bounding_u; ++j)
		{
			if (insideTriangle(i, j, t.pos))
			{
				auto Barycentric = computeBarycentric2D((float)i, (float)j, t.pos);
				float alpha = std::get<0>(Barycentric);
				float beta = std::get<1>(Barycentric);
				float gamma = std::get<2>(Barycentric);
				float w_reciprocal = 1.0f / (alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
				float z_interpolated = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
				z_interpolated *= w_reciprocal;

				// if current pixel should be painted, draw it using the color of the triangle t
				if (z_interpolated < z_buff[get_index(i, j)]) 
				{
					z_buff[get_index(i, j)] = z_interpolated;

					auto interpolated_color = alpha * t.color[0] + beta * t.color[1] + gamma * t.color[2];
					auto interpolated_normal = alpha * t.normal[0] + beta * t.normal[1] + gamma * t.normal[2];
					auto interpolated_texcoords = alpha * t.tex_coords[0] + beta * t.tex_coords[1] + gamma * t.tex_coords[2];
					auto interpolated_shadingcoords = alpha * world_pos[0] + beta * world_pos[1] + gamma * world_pos[2];
					fragment_shader_payload payload(interpolated_color, interpolated_normal.normalized(),
						interpolated_texcoords, tex ? &*tex : nullptr);
					payload.view_pos = interpolated_shadingcoords;
					auto pixel_color = fragment_shader(payload);

					Mymath::Vector3i current_pixel = { i, j, 0 };
					set_frame(current_pixel, pixel_color);
				}
			}
		}
	}

	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
		{
			int index_frame = i * width + j;
			int index_buff = (height - i - 1) * width + j;
			buff[index_buff * 3    ] = static_cast<unsigned int>(frame_buff[index_frame][0]);
			buff[index_buff * 3 + 1] = static_cast<unsigned int>(frame_buff[index_frame][1]);
			buff[index_buff * 3 + 2] = static_cast<unsigned int>(frame_buff[index_frame][2]);
		}
}
