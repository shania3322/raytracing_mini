#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "util.h"
#include "ray.h"

#define ASPECT_RATIO (16.0f/9.0f)

class Camera {
	public:
		Vec3 origin;
		Vec3 lower_left_corner;
		Vec3 move_x;
		Vec3 move_y;
		Vec3 move_z;

	public:
		Camera() {
			//float aspect_ratio = 16.0f/9.0f;
			float focal_length = 1.0f;
			float viewport_h = 1.0f;
			float viewport_w = viewport_h * ASPECT_RATIO;
			origin = Vec3(0.0f, 0.0f, 0.0f);
			move_x = Vec3(viewport_w, 0.0f, 0.0f);
			move_y = Vec3(0.0f, viewport_h, 0.0f);
			move_z = Vec3(0.0f, 0.0f, focal_length);
			lower_left_corner = origin-0.5f*move_y-0.5f*move_x-move_z;
		}

		Ray get_ray(float u, float v) {
			return Ray(origin, lower_left_corner+u*move_x+v*move_y-origin);
		}
};

#endif
