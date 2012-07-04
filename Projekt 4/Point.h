#pragma once
#include "Vector.h"

/*
 * Simple Point class that contains 3-dimensional coordinates and a normal vector
 * Author: Jannes Meyer
 */
struct Point {
	vec3 coord; // initialized with zeros
	vec3 normal;
	
	// Constructor
	Point() {}
	Point(vec3 v) : coord(v) {}
	Point(double x, double y, double z) {
		coord.x = x;
		coord.y = y;
		coord.z = z;
	}
};