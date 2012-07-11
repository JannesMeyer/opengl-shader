#include "Point.h"
#include "Color.h"
#include "Scene.h"
#include "FpsCounter.h"

#include <GL/glfw.h>
#include <memory>
#include <vector>
#include <string>
#include <exception>
#include <iostream>

struct Settings {
	int width;
	int height;
	bool wireframeEnabled;
	bool vsyncEnabled;
};
// Default settings
Settings settings = {800, 600, false, true};

// Global objects
std::shared_ptr<Scene> scene;


void init() {
	scene = std::make_shared<Scene>();
}


/*
 * Listen to key events
 */
void GLFWCALL onKeyEvent(int key, int action) {
	// Toggle vsync
	if (key == 'V' && action == GLFW_PRESS) {
		settings.vsyncEnabled = !settings.vsyncEnabled;
		glfwSwapInterval(static_cast<int>(settings.vsyncEnabled));
	}

	// Close window
	if (key == GLFW_KEY_ESC && action == GLFW_PRESS) {
		glfwCloseWindow();
		return;
	}
}

/*
 * These key events are executed continuously while the key
 * is held down, not just once per key press.
 */
void onInput() {
	// Rotate
	if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
		//scene->rotation += 1;
	} else if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
		//scene->rotation -= 1;
	}
	// Zoom
	if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
		//scene->scale += 0.01f;
	} else if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
		//scene->scale -= 0.01f;
	}
}

/*
 * Create an OpenGL context and a window
 */
void onInit() {
	// Initialize GLFW
	if (glfwInit() != GL_TRUE) {
		throw std::runtime_error("Couldn't initialize GLFW");
	}
	// Open a window with 8x AA
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	if (glfwOpenWindow(settings.width, settings.height, 8, 8, 8, 8, 24, 0, GLFW_WINDOW) != GL_TRUE) {
		glfwTerminate();
		throw std::runtime_error("Couldn't open an OpenGL window");
	}
	glfwSetWindowTitle("Projekt 4");
	glfwEnable(GLFW_STICKY_KEYS);
	glfwSetKeyCallback(onKeyEvent);

	// Initialize GL extension wrangler
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		throw std::runtime_error("Couldn't initialize the GL extension wrangler");
	}

	// Print OpenGL version
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl << std::endl;

	// Disable vsync if wanted
	if (!settings.vsyncEnabled) {
		glfwSwapInterval(0);
	}
}

/*
 * Setup the viewport and projection matrix
 */
void onReshape() {
	// Set viewport
	glViewport(0, 0, settings.width, settings.height);
	
	// Projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -7.5, 7.5, -10, 60);
}



/*
 * Main function
 */
int main() {
	// Initialize OpenGL
	try {
		onInit();
		onReshape();
	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		system("pause");
		return 1;
	}

	// Scene setup
	try {
		init();

	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		system("pause");
		return 1;
	}

	// Main loop
	FpsCounter fps;
	do {
		// Draw the scene and swap buffers
		scene->draw();
		glfwSwapBuffers();

		// Handle input
		onInput();
		
		// Signal a completed frame to the FpsCounter
		fps.tick();
	} while (glfwGetWindowParam(GLFW_OPENED));

	return 0;
}