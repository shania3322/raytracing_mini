#pragma once

#include "vec3.h"
#include <iostream>

void write_color(std::ostream &out, Color pixel_color){
	//write a single pixel color to standard output stream
	out << int(255.0f*pixel_color.x)<<' '
		<< int(255.0f*pixel_color.y)<<' '
		<< int(255.0f*pixel_color.z)<<'\n';
}
