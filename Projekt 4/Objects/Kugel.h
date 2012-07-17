#pragma once

#include "../ParametrisierteFlaeche.h"

class Kugel : public ParametrisierteFlaeche {
private:
	float radius;

public:
	Kugel(float radius);
	vec3 Evaluate(const vec2& domain) const;
};
