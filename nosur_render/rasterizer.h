#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include "triangle.h"

namespace rst 
{
	struct pos_buf_id
	{
		int pos_id = 0;
	};

	struct ind_buf_id
	{
		int ind_id = 0;
	};

	struct col_buf_id
	{
		int col_id = 0;
	};

	enum class Primitive
	{
		Line,
		Triangle
	};

	class rasterizer
	{
	public:
		rasterizer(int w, int h);

		pos_buf_id load_positions(const std::vector<Mymath::Vector3f>& positions);
		ind_buf_id load_indices(const std::vector<Mymath::Vector3i>& indices);
		col_buf_id load_colors(const std::vector<Mymath::Vector3f>& colors);

		inline void set_model(const Mymath::Matrix4f& m) { model = m; }
		inline void set_view(const Mymath::Matrix4f& v) { view = v; }
		inline void set_projection(const Mymath::Matrix4f& p) { projection = p; }

		void set_pixel(const Mymath::Vector3f& point, const Mymath::Vector3f& color);
		void clear();
        void draw(pos_buf_id pos_buffer, ind_buf_id ind_buffer, col_buf_id col_buffer, Primitive type);
		

	private:
		void draw_line(Mymath::Vector3f begin, Mymath::Vector3f end);

		Mymath::Matrix4f model;
		Mymath::Matrix4f view;
		Mymath::Matrix4f projection;

		std::map<int, std::vector<Mymath::Vector3f>> pos_buf;
		std::map<int, std::vector<Mymath::Vector3i>> ind_buf;
		std::map<int, std::vector<Mymath::Vector3f>> col_buf;

		int width, height;
		std::vector<Mymath::Vector3f> frame_buff;
		std::vector<float> z_buff;

		int next_id = 0;
		inline int get_next_id() { return next_id++; }
	};
}