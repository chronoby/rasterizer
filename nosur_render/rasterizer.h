#pragma once

#include <vector>
#include <algorithm>
#include "triangle.h"

namespace rst {
	class rasterizer
	{
	public:
		rasterizer(int w, int h);

		void load_positions(const std::vector<Mymath::Vector3f>& positions);
		void load_indices(const std::vector<Mymath::Vector3i>& indices);
		void load_colors(const std::vector<Mymath::Vector3f>& colors);

		inline void set_model(const Mymath::Matrix4f& m) { model = m; }
		inline void set_view(const Mymath::Matrix4f& v) { view = v; }
		inline void set_projection(const Mymath::Matrix4f& p) { projection = p; }

		void set_pixel(const Mymath::Vector3f& point, const Mymath::Vector3f& color);
		

	private:
		void draw_line(Mymath::Vector3f begin, Mymath::Vector3f end);

		Mymath::Matrix4f model;
		Mymath::Matrix4f view;
		Mymath::Matrix4f projection;

		int width, height;
		std::vector<Mymath::Vector3f> frame_buff;
		std::vector<float> z_buff;
	};
}