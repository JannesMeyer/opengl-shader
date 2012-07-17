#pragma once

#include "../ParametrisierteFlaeche.h"

class Klein : public ParametrisierteFlaeche {
private:
	float scale;
public:
	Klein(float scale);
	vec3 Evaluate(const vec2& domain) const;
	bool InvertNormal(const vec2& domain) const;
};