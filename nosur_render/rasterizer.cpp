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
	pos_buf.emplace(id, indices);
	return { id };
}

rst::col_buf_id rst::rasterizer::load_colors(const std::vector<Mymath::Vector3f>& colors)
{
	auto id = get_next_id();
	pos_buf.emplace(id, colors);
	return { id };
}

Mymath::Vector4f to_vec4(const Mymath::Vector3f& v3, float w = 1.0f)
{
	return Mymath::Vector4f(v3.x(), v3.y(), v3.z(), w);
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
			vec /= vec.w();
	}
}
