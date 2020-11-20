#pragma once

#include "util.h"
#include "texture.h"

class fragment_shader_payload
{
public:
	fragment_shader_payload() { }
	fragment_shader_payload(const Mymath::Vector3f& col, const Mymath::Vector3f& nor, 
		const Mymath::Vector2f& tc, texture* tex) :
		color(col), normal(nor), tex_coords(tc), text(tex) {  }
		
	texture* text = nullptr;
	Mymath::Vector3f view_pos;
	Mymath::Vector3f color;
	Mymath::Vector3f normal;
	Mymath::Vector2f tex_coords;
};

class vertex_shader_payload
{
public:
	Mymath::Vector3f position;
};

class light
{
public:
	Mymath::Vector3f position;
	Mymath::Vector3f intensity;
};

Mymath::Vector3f vertex_shader(vertex_shader_payload& payload);

Mymath::Vector3f normal_fragment_shader(const fragment_shader_payload& payload);

Mymath::Vector3f reflect(const Mymath::Vector3f& vec, const Mymath::Vector3f& axis);

Mymath::Vector3f phong_fragment_shader(const fragment_shader_payload& payload);

Mymath::Vector3f texture_fragment_shader(const fragment_shader_payload& payload);

Mymath::Vector3f displacement_fragment_shader(const fragment_shader_payload& payload);

Mymath::Vector3f bump_fragment_shader(const fragment_shader_payload& payload);
