#include "ParametrisierteFlaeche.h"

void ParametrisierteFlaeche::SetInterval(const ParametricInterval& interval) {
	m_divisions = interval.Divisions;
	m_upperBound = interval.UpperBound;
	m_slices = m_divisions - ivec2(1, 1);
}

int ParametrisierteFlaeche::GetVertexCount() const {
	return m_divisions.x * m_divisions.y;
}

int ParametrisierteFlaeche::GetTriangleIndexCount() const {
	return 6 * m_slices.x * m_slices.y;
}

vec2 ParametrisierteFlaeche::ComputeDomain(float x, float y) const {
	return vec2(x * m_upperBound.x / m_slices.x,
	            y * m_upperBound.y / m_slices.y);
}

void ParametrisierteFlaeche::GenerateVertices(VertexList& vertices) const {
	// Position
	int floatsPerVertex = 3;
	// Normalen
	floatsPerVertex += 3;

	// Resize the vector
	vertices.resize(GetVertexCount() * floatsPerVertex);
	float* attribute = &vertices[0];

	// Generate vertices
	for (int j = 0; j < m_divisions.y; j++) {
		for (int i = 0; i < m_divisions.x; i++) {

			// Compute Position
			vec2 domain = ComputeDomain(i, j);
			vec3 range = Evaluate(domain);
			attribute = range.Write(attribute);
			
			// Compute Normal
			float s = i, t = j;
			vec3 p = Evaluate(ComputeDomain(s, t));
			vec3 u = Evaluate(ComputeDomain(s + 0.01f, t)) - p;
			vec3 v = Evaluate(ComputeDomain(s, t + 0.01f)) - p;
			vec3 normal = u.Cross(v).Normalized();
			if (InvertNormal(domain))
				normal = -normal;
			attribute = normal.Write(attribute);
		}
	}
}

void ParametrisierteFlaeche::GenerateTriangleIndices(IndexList& indices) const {
	indices.resize(GetTriangleIndexCount());
	IndexList::iterator index = indices.begin();
	for (int j = 0, vertex = 0; j < m_slices.y; j++) {
		for (int i = 0; i < m_slices.x; i++) {
			int next = (i + 1) % m_divisions.x;
			*index++ = vertex + i;
			*index++ = vertex + next;
			*index++ = vertex + i + m_divisions.x;
			*index++ = vertex + next;
			*index++ = vertex + next + m_divisions.x;
			*index++ = vertex + i + m_divisions.x;
		}
		vertex += m_divisions.x;
	}
}