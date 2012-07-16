#pragma once
#include <GL/glew.h>

/*
 * Color class
 * Author: Jannes Meyer
 */
struct Color {
	GLfloat r, g, b, a;

	// Constructor
	Color() : r(0), g(0), b(0), a(1) {}
	Color(const GLfloat r, const GLfloat g, const GLfloat b) : r(r), g(g), b(b), a(1) {}
	Color(const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a) : r(r), g(g), b(b), a(a) {}
};