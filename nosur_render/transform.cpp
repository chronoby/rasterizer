#include "transform.h"

Mymath::Matrix4f get_view_matrix(Mymath::Vector3f eye_pos)
{
    float temp[16] = 
    { 
        1, 0, 0, -eye_pos[0], 
        0, 1, 0, -eye_pos[1], 
        0, 0, 1, -eye_pos[2], 
        0, 0, 0, 1 };
    Mymath::Matrix4f view(temp);
    return view;
}

Mymath::Matrix4f get_model_matrix(float rotation_angle)
{
    float rotation_radian = rotation_angle * MY_PI / 180;

    float m_rotation[16] = 
    { 
        cos(rotation_radian),  0, sin(rotation_radian), 0,
        0, 1, 0, 0,
        -sin(rotation_radian), 0, cos(rotation_radian), 0,
        0, 0, 0, 1 
    };
    Mymath::Matrix4f rotation(m_rotation);

    float m_scale[16] =
    {
        2.5, 0,   0,   0,
        0,   2.5, 0,   0,
        0,   0,   2.5, 0,
        0,   0,   0,   1
    };
    Mymath::Matrix4f scale(m_scale);

    float m_translate[16] =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    Mymath::Matrix4f translate(m_translate);

    return translate * rotation * scale;
}

Mymath::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
    float zNear, float zFar)
{
    float d = 1 / tan((eye_fov / 2) * MY_PI / 180);
    float A = -(zFar + zNear) / (zFar - zNear);
    float B = -2 * zFar * zNear / (zFar - zNear);

    float temp[16] = { d / aspect_ratio, 0, 0, 0,
        0, d, 0, 0,
        0, 0, A, B,
        0, 0, -1, 0 };
    Mymath::Matrix4f projection(temp);
    return projection;
}