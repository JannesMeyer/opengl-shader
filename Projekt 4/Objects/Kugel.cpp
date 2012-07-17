#include "Kugel.h"

// Constructor
Kugel::Kugel(float radius) : radius(radius) {
	ParametricInterval interval = {
		ivec2(20, 20), // Divisions for u and v
		vec2(Pi, TwoPi) // Upper bound for u and v
	};
	SetInterval(interval);
}

// Calculate a single point
vec3 Kugel::Evaluate(const vec2& domain) const {
	float u = domain.x;
	float v = domain.y;

	float x = radius * sin(u) * cos(v);
	float y = radius * cos(u);
	float z = radius * -sin(u) * sin(v);
	
	return vec3(x, y, z);
}
