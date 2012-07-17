#pragma once

#include "../ParametrisierteFlaeche.h"

class Torus : public ParametrisierteFlaeche {
private:
	float majorRadius;
	float minorRadius;

public:
	Torus(float majorRadius, float minorRadius);
	vec3 Evaluate(const vec2& domain) const;
};