#include "Point.h"
#include "Color.h"
#include "FpsCounter.h"
#include "util.h"

//#define GL_GLEXT_PROTOTYPES
#include <gl/glew.h>
#include <gl/glfw.h>
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
double alpha = 0;

// Global objects
GLuint vertexBuffer;
GLuint indexBuffer;

void init() {
	// Load data
	GLfloat vertexData[] = {0, 2, 0,  -2, -2, 0,   2, -2, 0};
	GLubyte indexData[] = {0, 1, 2};

	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
}

void render() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0, 0, -10);
    glRotated(alpha, 0, 0, 1);

    glColor3f(1, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glEnableVertexAttribArray(0);                                               //ENABLE VERTEX POSITION
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);      // VERTEX POSITION POINTER

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);
}

/*
 * Functions for creating OpenGL objects:
 */
//static GLuint make_buffer(GLenum target, const void *buffer_data, GLsizei buffer_size) {
//    GLuint buffer;
//    glGenBuffers(1, &buffer);
//    glBindBuffer(target, buffer);
//    glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
//    return buffer;
//}
//
//static GLuint make_texture(const char *filename) {
//    int width, height;
//    void *pixels = read_tga(filename, &width, &height);
//    GLuint texture;
//
//    if (!pixels)
//        return 0;
//
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
//    glTexImage2D(
//        GL_TEXTURE_2D, 0,           /* target, level */
//        GL_RGB8,                    /* internal format */
//        width, height, 0,           /* width, height, border */
//        GL_BGR, GL_UNSIGNED_BYTE,   /* external format, type */
//        pixels                      /* pixels */
//    );
//    free(pixels);
//    return texture;
//}

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
		alpha += 0.1;
	} else if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
		//scene->rotation -= 1;
		alpha -= 0.1;
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
	GLFWvidmode dtmode, modes[100];

	// Initialize GLFW
	if (!glfwInit()) {
		throw std::runtime_error("Couldn't initialize GLFW");
	}

	// Show desktop video mode
	glfwGetDesktopMode(&dtmode);
	int bits = dtmode.RedBits + dtmode.GreenBits + dtmode.BlueBits;
	std::cout << "Mode: " << dtmode.Width << " x " << dtmode.Height << " x " << bits << std::endl;

	// List available video modes
	int modecount = glfwGetVideoModes(modes, 100);
	std::cout << "Available modes:" << std::endl;
	for(int i = 0; i < modecount; ++i) {
		int bits = modes[i].RedBits + modes[i].GreenBits + modes[i].BlueBits;
		std::cout << modes[i].Width << " x " << modes[i].Height << " x " << bits << std::endl;
	}

	// Window hints
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	// Get an OpenGL 3.3 context
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// 8x AA
	//glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	// Open the window
	if (GL_TRUE != glfwOpenWindow(settings.width, settings.height, 8, 8, 8, 8, 24, 0, GLFW_WINDOW)) {
		glfwTerminate();
		throw std::runtime_error("Couldn't open an OpenGL window");
	}
	glfwSetWindowTitle("Projekt 4");
	//glfwSetWindowSizeCallback(resizeWindow);
	glfwEnable(GLFW_STICKY_KEYS);
	glfwSetKeyCallback(onKeyEvent);

	// GLEW doesn't work properly with the core profile.
	//glewExperimental = true
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

	// Set viewport
	glViewport(0, 0, settings.width, settings.height);


	// TODO: remove this
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspectRatio = 600.0f / 800.0f;
	glFrustum(0.5f, -0.5f, -0.5f * aspectRatio, 0.5f * aspectRatio, 1.0f, 50.0f);
	glMatrixMode(GL_MODELVIEW);
}



/*
 * Main function
 */
int main() {
	// Initialize OpenGL
	try {
		onInit();
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
		render();
		glfwSwapBuffers();

		// Handle input
		onInput();
		
		// Signal a completed frame to the FpsCounter
		fps.tick();
	} while (glfwGetWindowParam(GLFW_OPENED));

	return 0;
}