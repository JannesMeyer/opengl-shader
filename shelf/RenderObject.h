#pragma once
#include <GL/glew.h>

/*
 * Abstract class that represents an object which can be rendered
 * Author: Jannes Meyer
 */
class RenderObject
{
protected:
	GLenum mode;

public:
	RenderObject(GLenum mode = GL_FILL) : mode(mode) {}
	virtual void draw() = 0;

	// Subclasses can override this behavior
	virtual void setMode(GLenum mode) {
		glPolygonMode(GL_FRONT_AND_BACK, mode);
		this->mode = mode;
	}
};