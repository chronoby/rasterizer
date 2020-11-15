#include <algorithm>
#include <cmath>
#include "shader.h"

Mymath::Vector3f vertex_shader(vertex_shader_payload& payload)
{
	return payload.position;
}

Mymath::Vector3f normal_fragment_shader(const fragment_shader_payload& payload)
{
	Mymath::Vector3f return_color = (payload.normal.normalized() + Mymath::Vector3f(1.0f, 1.0f, 1.0f)) / 2.0f;
	Mymath::Vector3f result(static_cast<unsigned char>(return_color.x() * 255.0), 
		static_cast<unsigned char>(return_color.y() * 255.0), 
		static_cast<unsigned char>(return_color.z() * 255.0));
	return result;
}

Mymath::Vector3f reflect(Mymath::Vector3f& vec, Mymath::Vector3f& axis)
{
	auto costheta = vec.dot(axis);
	return (axis * (costheta * 2) - vec).normalized();
}

Mymath::Vector3f phone_fragment_shader(const fragment_shader_payload& payload)
{
    Mymath::Vector3f ka = Mymath::Vector3f(0.005, 0.005, 0.005);
    Mymath::Vector3f kd = Mymath::Vector3f(static_cast<float>(payload.color.x()), 
        static_cast<float>(payload.color.y()), static_cast<float>(payload.color.z()));
    Mymath::Vector3f ks = Mymath::Vector3f(0.7937, 0.7937, 0.7937);

    auto l1 = light{ {20, 20, 20}, {500, 500, 500} };
    auto l2 = light{ {-20, 20, 0}, {500, 500, 500} };

    std::vector<light> lights = { l1, l2 };
    Mymath::Vector3f amb_light_intensity{ 10, 10, 10 };
    Mymath::Vector3f eye_pos{ 0, 0, 10 };

    float p = 150;

    Mymath::Vector3f color = Mymath::Vector3f(static_cast<float>(payload.color.x()),
        static_cast<float>(payload.color.y()), static_cast<float>(payload.color.z()));
    Mymath::Vector3f point = payload.view_pos;
    Mymath::Vector3f normal = payload.normal;

    Mymath::Vector3f result_color = { 0, 0, 0 };
    for (auto& light : lights)
    {
        // components are. Then, accumulate that result on the *result_color* object.
        float distance_square = pow((light.position.x() - point.x()), 2) +
            pow((light.position.y() - point.y()), 2) +
            pow((light.position.z() - point.z()), 2);
        auto n = normal.normalized();

        // 1. diffuse light
        // Ld = kd * (I / r ^ 2) * max(0, n.dot(l))
        auto light_direction = (light.position - point).normalized();
        auto diffuse = kd.cwiseProduct((light.intensity / distance_square)) * std::max(0.f, n.dot(light_direction));

        // 2. ambient light
        // La = ka * Ia
        auto ambient = ka.cwiseProduct(amb_light_intensity);

        // 3. specular light
        // Ls = ks * (I / r ^ 2) * max(0, n.dot(h)) ^ p
        auto v = (eye_pos - point).normalized();
        auto h = (v + light_direction).normalized();
        auto specular = ks.cwiseProduct((light.intensity / distance_square)) * pow(std::max(0.f, n.dot(h)), p);

        result_color = result_color + diffuse + ambient + specular;
    }

    return result_color * 255.0f;
}

Mymath::Vector3f texture_fragment_shader(const fragment_shader_payload& payload)
{
    Mymath::Vector3f r_color;
    Mymath::Vector3f return_color = { 0, 0, 0 };
    if (payload.text)
    {
        // TODO: Get the texture value at the texture coordinates of the current fragment
        r_color = (*payload.text).getColor(payload.tex_coords.x(), payload.tex_coords.y());
        return_color = Mymath::Vector3f(static_cast<float>(r_color.x()), 
            static_cast<float>(r_color.y()), static_cast<float>(r_color.z()));
    }
    Mymath::Vector3f texture_color(return_color.x(), return_color.y(), return_color.z());

    Mymath::Vector3f ka = Mymath::Vector3f(0.005, 0.005, 0.005);
    Mymath::Vector3f kd = texture_color / 255.f;
    Mymath::Vector3f ks = Mymath::Vector3f(0.7937, 0.7937, 0.7937);

    auto l1 = light{ {20, 20, 20}, {500, 500, 500} };
    auto l2 = light{ {-20, 20, 0}, {500, 500, 500} };

    std::vector<light> lights = { l1, l2 };
    Mymath::Vector3f amb_light_intensity{ 10, 10, 10 };
    Mymath::Vector3f eye_pos{ 0, 0, 10 };

    float p = 150;

    Mymath::Vector3f color = texture_color;
    Mymath::Vector3f point = payload.view_pos;
    Mymath::Vector3f normal = payload.normal;

    Mymath::Vector3f result_color = { 0, 0, 0 };

    for (auto& light : lights)
    {
        // components are. Then, accumulate that result on the *result_color* object.
        float distance_square = pow((light.position.x() - point.x()), 2) +
            pow((light.position.y() - point.y()), 2) +
            pow((light.position.z() - point.z()), 2);
        auto n = normal.normalized();

        // 1. diffuse light
        // Ld = kd * (I / r ^ 2) * max(0, n.dot(l))
        auto light_direction = (light.position - point).normalized();
        auto diffuse = kd.cwiseProduct((light.intensity / distance_square)) * std::max(0.f, n.dot(light_direction));

        // 2. ambient light
        // La = ka * Ia
        auto ambient = ka.cwiseProduct(amb_light_intensity);

        // 3. specular light
        // Ls = ks * (I / r ^ 2) * max(0, n.dot(h)) ^ p
        auto v = (eye_pos - point).normalized();
        auto h = (v + light_direction).normalized();
        auto specular = ks.cwiseProduct((light.intensity / distance_square)) * pow(std::max(0.f, n.dot(h)), p);

        result_color = result_color + diffuse + ambient + specular;
    }

    return result_color * 255.0f;
}

Mymath::Vector3f displacement_fragment_shader(const fragment_shader_payload& payload);

Mymath::Vector3f bump_fragment_shader(const fragment_shader_payload& payload);
