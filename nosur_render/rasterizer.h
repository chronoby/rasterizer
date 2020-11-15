#pragma once

#include <vector>
#include <map>
#include <optional>
#include <algorithm>
#include <functional>

#include "triangle.h"
#include "shader.h"

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
		rasterizer() : width(0), height(0) {  }
		rasterizer(int w, int h);
		rasterizer(rasterizer& r) = default;

		pos_buf_id load_positions(const std::vector<Mymath::Vector3f>& positions);
		ind_buf_id load_indices(const std::vector<Mymath::Vector3i>& indices);
		col_buf_id load_colors(const std::vector<Mymath::Vector3f>& colors);

		inline void set_model(const Mymath::Matrix4f& m) { model = m; }
		inline void set_view(const Mymath::Matrix4f& v) { view = v; }
		inline void set_projection(const Mymath::Matrix4f& p) { projection = p; }

		inline void set_texture(texture t) { tex = t; }
		inline void set_vertex_shader(std::function<Mymath::Vector3f(vertex_shader_payload&)> vert_shader)
		{
			vertex_shader = vertex_shader;
		}
		inline void set_fragment_shader(std::function<Mymath::Vector3f(fragment_shader_payload&)> frag_shader)
		{
			fragment_shader = frag_shader;
		}

		void set_frame(const Mymath::Vector3i& point, const Mymath::Vector3f& color);
		void clear();
		void draw(std::vector<triangle*>& triangle_list);

		std::vector<Mymath::Vector3f>& frame_buffer() { return frame_buff; }

		unsigned char* buff = new unsigned char[700 * 700 * 3];
	private:
		void rasterize_triangle(const triangle& t, const std::array<Mymath::Vector3f, 3>& world_pos);

		Mymath::Matrix4f model;
		Mymath::Matrix4f view;
		Mymath::Matrix4f projection;

		std::map<int, std::vector<Mymath::Vector3f>> pos_buf;
		std::map<int, std::vector<Mymath::Vector3i>> ind_buf;
		std::map<int, std::vector<Mymath::Vector3f>> col_buf;
		std::map<int, std::vector<Mymath::Vector3f>> nor_buf;

		std::optional<texture> tex;

		std::function<Mymath::Vector3f(fragment_shader_payload&)> fragment_shader;
		std::function<Mymath::Vector3f(vertex_shader_payload&)> vertex_shader;

		int width, height;
		std::vector<Mymath::Vector3f> frame_buff;
		std::vector<float> z_buff;

		int next_id = 0;
		inline int get_next_id() { return next_id++; }
		inline int get_index(int x, int y){ return (height - 1 - y) * width + x; }
		
	};
}