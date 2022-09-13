#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "util.h"
#include "ray.h"
#include <tuple>
#include <cmath>

//#define ASPECT_RATIO (16.0f/9.0f)

class Camera {
	public:
		Vec3 origin;
		Vec3 lower_left_corner;
		Vec3 move_x;
		Vec3 move_y;
		Vec3 move_z;
		Vec3 n;
		Vec3 u;
		Vec3 v;

		// The diameter of the hole. Different from the real
		// aperture which is f/diameter.
		float aperture;


	public:
		Camera(Vec3 eye, Vec3 at, Vec3 vup, float fov,float ASPECT_RATIO,
				float aper, float focus_dist) : aperture(aper){
			// Get camera coordinates
			n = unit_vector(eye-at);
			u = unit_vector(cross(vup,n));
			v = cross(n,u);

			float focal_length = 1.0f;
			float viewport_h = tan(degree2rad(fov)/2.0f)*focal_length*2.0f;
			float viewport_w = viewport_h * ASPECT_RATIO;
			origin = eye;
			move_x = viewport_w*u;
			move_y = viewport_h*v;
			move_z = focal_length*n;

			// Precompute focus plane:
			// tan(theta/2) = h/f = h_focus_plane/focus_distance
			move_x = focus_dist*move_x;
			move_y = focus_dist*move_y;
			move_z = focus_dist*move_z;
			lower_left_corner = origin-0.5f*move_y-0.5f*move_x-move_z;
		}


		Ray get_ray(float du, float dv) {
			//Imitate aperture by shooting rays from a disc.
			Vec3 t = random_in_disc(aperture/2.0f);
	 		Vec3 next_point = origin+t.x*u+t.y*v;

			//shoot ray towards focus plane.
			Vec3 direction = lower_left_corner+du*move_x+dv*move_y-next_point;
			return Ray(next_point,unit_vector(direction));
		}
};

#endif
