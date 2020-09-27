#pragma once

#include "util.h"

Mymath::Matrix4f get_view_matrix(Mymath::Vector3f eye_pos);

Mymath::Matrix4f get_model_matrix(float rotation_angle);

Mymath::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
    float zNear, float zFar);