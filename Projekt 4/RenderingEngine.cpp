#include "RenderingEngine.h"
#include "Vector.hpp"
#include "Matrix.hpp"

#include <cmath>
#include <iostream>
#include <exception>

// Load the shader source code into strings using the STRINGIFY macro
#define STRINGIFY(A)  #A
#include "Shaders/Simple.v.glsl"
#include "Shaders/Simple.f.glsl"

// Constructor
RenderingEngine::RenderingEngine(int width, int height) {
    const float coneRadius = 0.5f;
    const float coneHeight = 1.866f;
    const int coneSlices = 40;
    
	// Bottom of the cone
    {
        // Allocate space for the cone vertices.
        cone.resize((coneSlices + 1) * 2);
        
        // Initialize the vertices of the triangle strip.
        auto vertex = std::begin(cone);
        const float dtheta = TwoPi / coneSlices;
        for (float theta = 0; vertex != std::end(cone); theta += dtheta) {
            
            // Grayscale gradient (this is cheating, no real lighting)
            float brightness = abs(sin(theta));
            vec4 color (brightness, brightness, brightness, 1);
            
            // Top vertex
            vertex->position = vec3(0, 1, 0);
            vertex->color = color;
            vertex++;
            
            // Circle vertex
            vertex->position.x = coneRadius * cos(theta);
            vertex->position.y = 1 - coneHeight;
            vertex->position.z = coneRadius * sin(theta);
            vertex->color = color;
            vertex++;
        }
    }
    
	// Bottom cap
    {
        // Allocate space for the disk vertices.
        disk.resize(coneSlices + 2);
        
        // Initialize the center vertex of the triangle fan.
        auto vertex = std::begin(disk);
        vertex->color = vec4(0.75, 0.75, 0.75, 1);
        vertex->position.x = 0;
        vertex->position.y = 1 - coneHeight;
        vertex->position.z = 0;
        vertex++;
        
        // Initialize the rim vertices of the triangle fan.
        const float dtheta = TwoPi / coneSlices;
        for (float theta = 0; vertex != std::end(disk); theta += dtheta) {
            vertex->color = vec4(0.75, 0.75, 0.75, 1);
            vertex->position.x = coneRadius * cos(theta);
            vertex->position.y = 1 - coneHeight;
            vertex->position.z = coneRadius * sin(theta);
            vertex++;
        }
    }
    
    // Set up some GL state.
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
	
	// Build the vertex and fragment shader
	simpleProgram = buildProgram(SimpleVertexShader, SimpleFragmentShader);
	// Use our compiled program
	glUseProgram(simpleProgram);

    // Set the projection matrix.
    GLint projectionUniform = glGetUniformLocation(simpleProgram, "Projection");
    //mat4 projectionMatrix = mat4::Frustum(-1.6f, 1.6, -2.4, 2.4, 5, 10);
	mat4 projectionMatrix = mat4::Frustum(-4, 4, -3, 3, 5, 10);
    glUniformMatrix4fv(projectionUniform, 1, 0, projectionMatrix.Pointer());
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

void RenderingEngine::render() const {
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	GLuint positionSlot = glGetAttribLocation(simpleProgram, "Position");
	GLuint colorSlot = glGetAttribLocation(simpleProgram, "SourceColor");

	// Enable position and color arrays
    glEnableVertexAttribArray(positionSlot);
    glEnableVertexAttribArray(colorSlot);
    
	// Get the rotation and translation matrices
    mat4 rotation(animation.current.ToMatrix());
    mat4 translation = mat4::Translate(0, 0, -7);

    // Set the model-view matrix
    GLint modelviewUniform = glGetUniformLocation(simpleProgram, "Modelview");
    mat4 modelviewMatrix = rotation * translation;
    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.Pointer());
    
    // Draw the cone
    {
      GLsizei elementSize = sizeof(Vertex);
      const GLvoid* pCoords = &cone[0].position.x;
      const GLvoid* pColors = &cone[0].color.x;
      glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, elementSize, pCoords); // slot, dimensions, type, , step size, memory address
      glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, elementSize, pColors);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, cone.size());
    }
    
    // Draw the bottom circle
    {
      GLsizei elementSize = sizeof(Vertex);
      const GLvoid* pCoords = &disk[0].position.x;
      const GLvoid* pColors = &disk[0].color.x;
      glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, elementSize, pCoords);
      glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, elementSize, pColors);
      glDrawArrays(GL_TRIANGLE_FAN, 0, disk.size());
    }

	// Disable position and color arrays
    glDisableVertexAttribArray(positionSlot);
    glDisableVertexAttribArray(colorSlot);
}

void RenderingEngine::updateAnimation(double timeStep) {
	// Constants
	static const float duration = 0.5f;

	// Don't change anything if the animation is finished
    if (animation.current == animation.end) {
        return;
	}
    
	// Advance the animation
    animation.elapsed += timeStep;
    if (animation.elapsed >= duration) {
		std::cout << "Animation finished" << std::endl;
		// Set the current direction to be exactly the end direction
        animation.current = animation.end;
    } else {
        float mu = animation.elapsed / duration;
		// Calculate intermediary direction
        animation.current = animation.start.Slerp(mu, animation.end);
    }
}

// Expects the direction to rotate to
void RenderingEngine::rotate(vec3 direction) {
	std::cout << "Animation started" << std::endl;
    animation.elapsed = 0;
    animation.start = animation.current;
    animation.end = Quaternion::CreateFromVectors(vec3(0, 1, 0), direction);
}