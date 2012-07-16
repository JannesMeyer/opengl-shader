#include "Scene.h"

Scene::Scene(bool lightingEnabled) : rotation(0), scale(1) {
	// Background color
	glClearColor(1, 1, 1, 1);
	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);

}

void Scene::add(std::shared_ptr<RenderObject> object) {
	renderObjects.push_back(object);
}

const void Scene::draw() {
	// Clear background and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Objects
	//gluSphere(gluNewQuadric(), 2, 50, 50);
	for (auto& object : renderObjects) {
		object->draw();
	}
}