#include "FpsCounter.h"
#include "RenderingEngine.h"

//#define GL_GLEXT_PROTOTYPES
#include <gl/glew.h>
#include <gl/glfw.h>
#include <memory>
#include <vector>
#include <string>
#include <exception>
#include <iostream>
#include <string>

struct Settings {
	int width;
	int height;
	bool wireframeEnabled;
	bool vsyncEnabled;
};
// Default settings
Settings settings = {800, 600, false, true};

// Rendering engine
RenderingEngine* renderingEngine;
float alpha = 0;

/*
 * Print a log message
 */
void log(std::string message) {
#ifndef NDEBUG
	std::cout << message << std::endl;
#endif
}


/*
 * Listen to key events
 */
void GLFWCALL onKeyEvent(int key, int action) {
	// Toggle vsync
	if (key == 'V' && action == GLFW_PRESS) {
		settings.vsyncEnabled = !settings.vsyncEnabled;
		glfwSwapInterval(static_cast<int>(settings.vsyncEnabled));
		
		// Write to the log
		if (settings.vsyncEnabled) {
			log("vsync: on");
		} else {
			log("vsync: off");
		}
	}
	
	// Rotate
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		//renderingEngine->rotate(vec3(-1, 0, 0));
		alpha += 0.1f;
	} else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		//renderingEngine->rotate(vec3(1, 0, 0));
		alpha -= 0.1f;
	} else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		//renderingEngine->rotate(vec3(0, 1, 0));
	} else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		//renderingEngine->rotate(vec3(0, -1, 0));
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
		alpha += 0.1f;
	} else if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
		alpha -= 0.1f;
	}
}

/*
 * Create an OpenGL context and a window
 */
void createWindow() {
	// Initialize GLFW
	if (!glfwInit()) {
		throw std::runtime_error("Couldn't initialize GLFW");
	}

	// Show desktop video mode
	GLFWvidmode mode;
	glfwGetDesktopMode(&mode);
	int bits = mode.RedBits + mode.GreenBits + mode.BlueBits;
	std::cout << "Display: " << mode.Width << " x " << mode.Height << " x " << bits << std::endl;

	// Open a window
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	// Get an OpenGL 3.3 context
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// 8x AA (doesn't work with OpenGL 3.3)
	//glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);

	// Define our buffer settings
	int redBits = 8;
	int greenBits = 8;
	int blueBits = 8;
	int alphaBits = 8;
	int depthBits = 32;
	int stencilBits = 0;

	if (GL_TRUE != glfwOpenWindow(settings.width, settings.height, redBits, greenBits, blueBits, alphaBits, depthBits, stencilBits, GLFW_WINDOW)) {
		glfwTerminate();
		throw std::runtime_error("Couldn't open an OpenGL window");
	}
	glfwSetWindowTitle("Shaders - Projekt 4");
	//glfwSetWindowSizeCallback(resizeWindow);
	glfwEnable(GLFW_STICKY_KEYS);
	glfwSetKeyCallback(onKeyEvent);

	// Initialize GL extension wrangler
	// (GLEW doesn't work properly with the core profile)
	//glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		glfwTerminate();
		std::cout << glewGetErrorString(error) << std::endl;
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
 * Main function
 */
int main() {
	// Initialize OpenGL
	try {
		createWindow();
	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}

	// Scene setup
	try {
		renderingEngine = new RenderingEngine(settings.width, settings.height);
	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}

	// Main loop
	FpsCounter fps;
	double oldTime = glfwGetTime();
	do {
		// Update the animation
		double currentTime = glfwGetTime();
		double deltaSeconds = currentTime - oldTime;
		oldTime = currentTime;
		//renderingEngine->updateAnimation(deltaSeconds);

		// Draw the scene and swap buffers
		renderingEngine->render(alpha);
		glfwSwapBuffers();

		// Handle input
		onInput();
		
		// Signal a completed frame to the FpsCounter
		fps.tick();
	} while (glfwGetWindowParam(GLFW_OPENED));

	return 0;
}