#include "Scene.h"

Scene::Scene(bool lightingEnabled) : rotation(0), scale(1) {
	// Background color
	glClearColor(1, 1, 1, 1);
	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	if (lightingEnabled) {
		lighting();
	}
}

void Scene::add(std::shared_ptr<RenderObject> object) {
	renderObjects.push_back(object);
}

const void Scene::lighting() {
	GLfloat position[4] = {10, 5, 10,  1};
	GLfloat ambient[4] = {0.3f,  0.3f,  0.3f,  1.0f};
	GLfloat diffuse[4] = {1.0f,  1.0f,  1.0f,  1.0f};
	//GLfloat specular[4] = {1.0f,  1.0f,  1.0f,  1.0f};

	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  diffuse);
	//glLightfv(GL_LIGHT1, GL_SPECULAR,  specular);

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
}

const void Scene::setMaterialColor(GLfloat r, GLfloat g, GLfloat b) {
	GLfloat ambient[4] = {r*0.5f, g*0.5f, b*0.5f, 1};
	GLfloat diffuse[4] = {r, g, b, 1};
	GLfloat specular[4] = {r*0.5f, g*0.5f, b*0.5f, 1};
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
}

const void Scene::draw() {
	// Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Camera
	glTranslatef(0, 0, -10); // Move 10 units backwards in z, since camera is at origin
	// Rotation
	glRotatef(10, 1, 0, 0);
	glRotatef(rotation, 0, 1, 0);
	// Translation
	glTranslatef(0, -2, 0);
	// Scale
	glScalef(scale, scale, scale);

	// Clear background and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Objects
	//glEnable(GL_NORMALIZE);
	glEnable(GL_RESCALE_NORMAL); // More efficient than GL_NORMALIZE
	//setMaterialColor(1, 0, 0);
	//gluSphere(gluNewQuadric(), 2, 50, 50);
	for (auto& object : renderObjects) {
		object->draw();
	}
}

void Scene::setPolygonMode(GLenum mode) {
	for (auto& object : renderObjects) {
		object->setMode(mode);
	}
}