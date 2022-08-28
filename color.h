#pragma once

#include "vec3.h"
#include "util.h"
#include <iostream>


void write_color(std::ostream &out, Color pixel_color, int samples_per_pixel){
	float r = (1.0f/float(samples_per_pixel))*pixel_color.x;
	float g = (1.0f/float(samples_per_pixel))*pixel_color.y;
	float b = (1.0f/float(samples_per_pixel))*pixel_color.z;

	//write a single pixel color to standard output stream
	out << int(255.0f*clamp(r,0.0f,0.9999f))<<' '
		<< int(255.0f*clamp(g,0.0f,0.9999f))<<' '
		<< int(255.0f*clamp(b,0.0f,0.9999f))<<'\n';
}
