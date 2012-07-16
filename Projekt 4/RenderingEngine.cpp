#include "RenderingEngine.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>
#include <exception>

#define STRINGIFY(A)  #A
#include "Shaders/Simple.v.glsl"
#include "Shaders/Simple.f.glsl"

struct Vertex {
	float Position[2];
	float Color[4];
};

// Define the positions and colors of two triangles.
const Vertex vertices[] = {
	{{-0.5f, -0.866f}, {1, 1, 0.5f, 1}},
	{{0.5f,  -0.866f}, {1, 1, 0.5f, 1}},
	{{0,      1},      {1, 1, 0.5f, 1}},
	{{-0.5f, -0.866f}, {0.5f, 0.5f, 0.5f}},
	{{0.5f,  -0.866f}, {0.5f, 0.5f, 0.5f}},
	{{0,     -0.4f},   {0.5f, 0.5f, 0.5f}},
};

// Constructor
RenderingEngine::RenderingEngine(int width, int height) : currentAngle(0.0f) {
	// Create & bind the color buffer so that the caller can allocate its space.
	//glGenRenderbuffers(1, &renderbuffer);
	//glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);

	// Create the framebuffer object and attach the color buffer.
	//glGenFramebuffers(1, &framebuffer);
	//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer);
	
	glViewport(0, 0, width, height);
	
	// Build the vertex and fragment shader
	simpleProgram = buildProgram(SimpleVertexShader, SimpleFragmentShader);
	// Use our compiled program
	glUseProgram(simpleProgram);
	
	// Initialize the projection matrix.
	applyOrtho(2, 3);
	
	// Initialize rotation animation state
	currentAngle = 0;
}

GLuint RenderingEngine::buildProgram(const char* vertexShaderSource, const char* fragmentShaderSource) const {
	// Build shaders
	GLuint vertexShader = buildShader(vertexShaderSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = buildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	
	// Create program and attach shaders
	GLuint programHandle = glCreateProgram();
	glAttachShader(programHandle, vertexShader);
	glAttachShader(programHandle, fragmentShader);
	// Link the shaders together
	glLinkProgram(programHandle);
	
	// Print an error message if something went wrong
	GLint linkSuccess;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
	if (linkSuccess == GL_FALSE) {
		GLchar messages[256];
		glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
		std::cout << "Link error" << std::endl;
		throw new std::runtime_error(messages);
	}
	
	return programHandle;
}

GLuint RenderingEngine::buildShader(const char* source, GLenum shaderType) const {
	// Create a GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
	GLuint shaderHandle = glCreateShader(shaderType);
	// Load the shader source code into graphics memory
	glShaderSource(shaderHandle, 1, &source, 0);
	// Compile the shader
	glCompileShader(shaderHandle);
	
	// Print an error message if something went wrong
	GLint compileSuccess;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
	if (compileSuccess == GL_FALSE) {
		GLchar messages[256];
		glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
		std::cout << "Shader compile error" << std::endl;
		throw new std::runtime_error(messages);
	}
	
	return shaderHandle;
}

void RenderingEngine::applyOrtho(float maxX, float maxY) const {
	float a = 1.0f / maxX;
	float b = 1.0f / maxY;
	float ortho[16] = {
		a, 0,  0, 0,
		0, b,  0, 0,
		0, 0, -1, 0,
		0, 0,  0, 1
	};
	
	GLint projectionUniform = glGetUniformLocation(simpleProgram, "Projection");
	glUniformMatrix4fv(projectionUniform, 1, 0, &ortho[0]);
}

void RenderingEngine::applyRotation(float degrees) const {
	float radians = degrees * 3.14159f / 180.0f;
	float s = std::sin(radians);
	float c = std::cos(radians);
	float zRotation[16] = {
		c, s, 0, 0,
	   -s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	
	GLint modelviewUniform = glGetUniformLocation(simpleProgram, "Modelview");
	glUniformMatrix4fv(modelviewUniform, 1, 0, &zRotation[0]);
}

void RenderingEngine::render() const {
	glClearColor(0.5f, 0.5f, 0.5f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	applyRotation(currentAngle);
	
	GLuint positionSlot = glGetAttribLocation(simpleProgram, "Position");
	GLuint colorSlot = glGetAttribLocation(simpleProgram, "SourceColor");
	
	// Enable position and color arrays
	glEnableVertexAttribArray(positionSlot);
	glEnableVertexAttribArray(colorSlot);
	
	GLsizei elementSize = sizeof(Vertex);
	const GLvoid* pCoords = &vertices[0].Position[0];
	const GLvoid* pColors = &vertices[0].Color[0];
	
	glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, elementSize, pCoords);
	glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, elementSize, pColors);
	
	GLsizei vertexCount = sizeof(vertices) / sizeof(Vertex);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	
	// Enable position and color arrays
	glDisableVertexAttribArray(positionSlot);
	glDisableVertexAttribArray(colorSlot);
}

void RenderingEngine::updateRotation(float rotation) {
	currentAngle = rotation;
}