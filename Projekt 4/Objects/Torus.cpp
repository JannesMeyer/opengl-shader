#include "Torus.h"

// Constructor
Torus::Torus(float majorRadius, float minorRadius) : majorRadius(majorRadius), minorRadius(minorRadius) {
	ParametricInterval interval = {
		ivec2(20, 20), // Divisions for u and v
		vec2(TwoPi, TwoPi) // Upper bound for u and v
	};
	SetInterval(interval);
}

// Calculate a single point
vec3 Torus::Evaluate(const vec2& domain) const {
	float u = domain.x;
	float v = domain.y;

	float x = (majorRadius + minorRadius * cos(v)) * cos(u);
	float y = (majorRadius + minorRadius * cos(v)) * sin(u);
	float z = minorRadius * sin(v);

	return vec3(x, y, z);
}