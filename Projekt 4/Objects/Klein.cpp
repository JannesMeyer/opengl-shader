#include "Klein.h"

/*
 * Klein
 * Eine parametrisierte Fläche, die eine Kleinsche Flasche generiert
 */
Klein::Klein(float scale) : scale(scale) {
	ParametricInterval interval = {
		ivec2(30, 40),
		vec2(TwoPi, TwoPi)
	};
	SetInterval(interval);
}

// Calculate a single point
vec3 Klein::Evaluate(const vec2& domain) const {
	float v = 1 - domain.x;
	float u = domain.y;
		
	float x0 = 3 * cos(u) * (1 + sin(u)) + (2 * (1 - cos(u) / 2)) * cos(u) * cos(v);
	float y0  = 8 * sin(u) + (2 * (1 - cos(u) / 2)) * sin(u) * cos(v);
		
	float x1 = 3 * cos(u) * (1 + sin(u)) + (2 * (1 - cos(u) / 2)) * cos(v + Pi);
	float y1 = 8 * sin(u);
		
	vec3 range;
	range.x = u < Pi ? x0 : x1;
	range.y = u < Pi ? -y0 : -y1;
	range.z = (-2 * (1 - cos(u) / 2)) * sin(v);
	return range * scale;
}
bool Klein::InvertNormal(const vec2& domain) const {
	return domain.y > 3 * Pi / 2;
}
