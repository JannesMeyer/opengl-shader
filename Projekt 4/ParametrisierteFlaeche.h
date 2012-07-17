#pragma once

#include "Vector.hpp"
#include <vector>

typedef std::vector<float> VertexList;
typedef std::vector<unsigned short> IndexList;

//struct Vertex {
//    vec3 position;
//    vec4 color;
//};

struct ParametricInterval {
	ivec2 Divisions;
	vec2 UpperBound;
};

/*
 * Abstrakte Klasse, die eine Fläche repräsentiert
 */
class Flaeche {
public:
    virtual int GetVertexCount() const = 0;
    virtual int GetTriangleIndexCount() const = 0;
    virtual void GenerateVertices(VertexList& vertices) const = 0;
    virtual void GenerateTriangleIndices(IndexList& indices) const = 0;
    virtual ~Flaeche() {} // Q: causes this a memory leaks?
};

/*
 * Klasse zur Berechnung von parametrisierten Flächen
 */
class ParametrisierteFlaeche : public Flaeche {
private:
	vec2 ComputeDomain(float i, float j) const;
	ivec2 m_slices;
	ivec2 m_divisions;
	vec2 m_upperBound;
	vec2 m_textureCount;

protected:
	void SetInterval(const ParametricInterval& interval);
	virtual vec3 Evaluate(const vec2& domain) const = 0;
	virtual bool InvertNormal(const vec2& domain) const { return false; }
	virtual bool UseDomainCoords() const { return true; }

public:
	int GetVertexCount() const;
	int GetTriangleIndexCount() const;
	void GenerateVertices(VertexList& vertices) const;
	void GenerateTriangleIndices(IndexList& indices) const;
};

