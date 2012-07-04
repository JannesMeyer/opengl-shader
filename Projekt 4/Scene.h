#pragma once
#include "RenderObject.h"
#include <GL/glew.h>
#include <memory>
#include <vector>

class Scene
{
private:
	std::vector<std::shared_ptr<RenderObject>> renderObjects;
public:
	GLfloat rotation;
	GLfloat scale;

	Scene(bool lightingEnabled = true);
	void add(std::shared_ptr<RenderObject> object);
	const void lighting();
	const void setMaterialColor(GLfloat r, GLfloat g, GLfloat b);
	const void draw();
	void setPolygonMode(GLenum mode);
};

