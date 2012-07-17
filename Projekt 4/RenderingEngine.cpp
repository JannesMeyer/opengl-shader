#include "RenderingEngine.h"
#include "Vector.hpp"
#include "Matrix.hpp"

#include <cmath>
#include <iostream>
#include <exception>

// Load the shader source code into strings using the STRINGIFY macro
#define STRINGIFY(A)  #A
//#include "Shaders/Simple.vert"
//#include "Shaders/Simple.frag"
//#include "Shaders/Lighting.vert"
//#include "Shaders/Lighting.frag"
#include "Shaders/ToonLighting.vert"
#include "Shaders/ToonLighting.frag"


// Constructor
RenderingEngine::RenderingEngine(int width, int height) {
	// Generate some vertex geometry
	torus = createDrawable(Torus(1.4, 0.3));
	kugel = createDrawable(Kugel(2));
	klein = createDrawable(Klein(0.4));
	
    // Save the viewport size
	size.x = width;
	size.y = height;
	
	// Create the GLSL programs
    buildProgram(SimpleVertexShader, SimpleFragmentShader, p1);

    // Set up some default material parameters
    glUseProgram(p1.program);
    glUniform3f(p1.uniforms.DiffuseMaterial, 0.75f, 0.25f, 0);
    glUniform3f(p1.uniforms.AmbientMaterial, 0.04f, 0.04f, 0.04f);
    glUniform3f(p1.uniforms.SpecularMaterial, 0.6f, 0.5f, 0.5f);
    glUniform1f(p1.uniforms.Shininess, 50);
    
    // Set up the transforms
    //const float nearPlane = 5, farPlane = 50;
    //const float scale = 0.004;
    //const float halfWidth = scale * size.x / 2;
    //const float halfHeight = scale * size.y / 2;
    //mat4 projection = mat4::Frustum(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane);
	mat4 projection = mat4::Frustum(-4, 4, -3, 3, 5, 10); // 4:3 aspect ratio
	glUniformMatrix4fv(p1.uniforms.Projection, 1, 0, projection.Pointer());
}

/*
 * Creates a "Drawable" struct using a parametric surface
 */
Drawable RenderingEngine::createDrawable(const ParametrisierteFlaeche& surface) const {
    // Create the VBO for the vertices
    VertexList vertices;
    surface.GenerateVertices(vertices); // Call by reference

	// Handle for the vertex buffer
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
    
    // Create a new VBO for the indices if needed.
    int indexCount = surface.GetTriangleIndexCount();
	// Handle for the index buffer
    GLuint indexBuffer;
    IndexList indices(indexCount);
    surface.GenerateTriangleIndices(indices);
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLushort), &indices[0], GL_STATIC_DRAW);
    
    // Fill in the struct
    Drawable drawable;
    drawable.indexBuffer = indexBuffer;
    drawable.vertexBuffer = vertexBuffer;
    drawable.indexCount = indexCount;
    return drawable;
}

/*
 * Create a program
 */
void RenderingEngine::buildProgram(const char* vertexShaderSource, const char* fragmentShaderSource, ProgramHandles& program) const {
	// Build shader
    GLuint vertexShader = buildShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = buildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    
	// Create program and attach shaders
    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
	// Link the shaders
    glLinkProgram(programHandle);
    
	// Print an error message if something went wrong
    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
		std::cout << "Shader linker errors: " << std::endl << messages << std::endl;
		exit(1);
		//throw new std::runtime_error(messages);
    }
    
	// Save the program handle
    program.program = programHandle;

	// Get attribute handles
    program.attributes.position = glGetAttribLocation(programHandle, "Position");
    program.attributes.normal = glGetAttribLocation(programHandle, "Normal");
    
	// Get uniform handles
    program.uniforms.Projection = glGetUniformLocation(programHandle, "Projection");
    program.uniforms.Modelview = glGetUniformLocation(programHandle, "Modelview");
    program.uniforms.NormalMatrix = glGetUniformLocation(programHandle, "NormalMatrix");
    program.uniforms.LightPosition = glGetUniformLocation(programHandle, "LightPosition");
    program.uniforms.AmbientMaterial = glGetUniformLocation(programHandle, "AmbientMaterial");
    program.uniforms.DiffuseMaterial = glGetUniformLocation(programHandle, "DiffuseMaterial");
    program.uniforms.SpecularMaterial = glGetUniformLocation(programHandle, "SpecularMaterial");
    program.uniforms.Shininess = glGetUniformLocation(programHandle, "Shininess");
}

GLuint RenderingEngine::buildShader(const char* source, GLenum shaderType) const
{
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
		if (shaderType == GL_VERTEX_SHADER) {
			std::cout << "Vertex ";
		} else {
			std::cout << "Fragment ";
		}
		std::cout << "Shader compiler errors: " << std::endl << messages << std::endl;
		exit(1);
		//throw new std::runtime_error(messages);
    }
    
    return shaderHandle;
}

//void RenderingEngine::render() const {
//    glClearColor(0.5f, 0.5f, 0.5f, 1);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
//	GLuint positionSlot = glGetAttribLocation(simpleProgram, "Position");
//	GLuint colorSlot = glGetAttribLocation(simpleProgram, "SourceColor");
//
//	// Enable position and color arrays
//    glEnableVertexAttribArray(positionSlot);
//    glEnableVertexAttribArray(colorSlot);
//    
//	// Get the rotation and translation matrices
//    mat4 rotation(animation.current.ToMatrix());
//    mat4 translation = mat4::Translate(0, 0, -7);
//
//    // Set the model-view matrix
//    GLint modelviewUniform = glGetUniformLocation(simpleProgram, "Modelview");
//    mat4 modelviewMatrix = rotation * translation;
//    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.Pointer());
//    
//    // Draw the cone
//    {
//      GLsizei elementSize = sizeof(Vertex);
//      const GLvoid* pCoords = &cone[0].position.x;
//      const GLvoid* pColors = &cone[0].color.x;
//      glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, elementSize, pCoords); // slot, dimensions, type, , step size, memory address
//      glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, elementSize, pColors);
//      glDrawArrays(GL_TRIANGLE_STRIP, 0, cone.size());
//    }
//    
//    // Draw the bottom circle
//    {
//      GLsizei elementSize = sizeof(Vertex);
//      const GLvoid* pCoords = &disk[0].position.x;
//      const GLvoid* pColors = &disk[0].color.x;
//      glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, elementSize, pCoords);
//      glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, elementSize, pColors);
//      glDrawArrays(GL_TRIANGLE_FAN, 0, disk.size());
//    }
//
//	// Disable position and color arrays
//    glDisableVertexAttribArray(positionSlot);
//    glDisableVertexAttribArray(colorSlot);
//}

void RenderingEngine::render(float theta) const {
	// Clear background color
	glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set viewport size
    glViewport(0, 0, size.x, size.y); // 0, 0 is the BOTTOM-LEFT
    glEnable(GL_DEPTH_TEST);

    // Set the light position
    glUseProgram(p1.program);
    vec4 lightPosition(0.25, 0.25, 1, 0);
    glUniform3fv(p1.uniforms.LightPosition, 1, lightPosition.Pointer());

    // Set the model-view transform
    const float distance = 8;
    const vec3 target(0, -0.15, 0);
    const vec3 up(0, 1, 0);
    const vec3 eye = vec3(0, 0, distance);
    const mat4 view = mat4::LookAt(eye, target, up);
    const mat4 model = mat4::RotateY(theta * 180.0f / 3.14f);
    const mat4 modelview = model * view;
    glUniformMatrix4fv(p1.uniforms.Modelview, 1, 0, modelview.Pointer());

    // Set the normal matrix:
    mat3 normalMatrix = modelview.ToMat3();
    glUniformMatrix3fv(p1.uniforms.NormalMatrix, 1, 0, normalMatrix.Pointer());

    // Render the Torus
	//renderDrawable(torus, p1);

    //renderDrawable(kugel, p1);

	glDepthFunc(GL_LESS);
	renderDrawable(klein, p1);
}


void RenderingEngine::renderDrawable(const Drawable& drawable, const ProgramHandles& program) const {
	// Position
    int elementSize = sizeof(vec3);
	// Normals
	elementSize += sizeof(vec3);
    
	// Offset
    GLvoid* offset = (GLvoid*) sizeof(vec3);
    
	// Create an alias for the attributes
    const AttributeHandles& a = program.attributes;
    
	// Bind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, drawable.vertexBuffer);

	// Supply vertex position handle
    glEnableVertexAttribArray(a.position);
    glVertexAttribPointer(a.position, 3, GL_FLOAT, GL_FALSE, elementSize, 0);
    
	// Supply vertex normal handle
    glEnableVertexAttribArray(a.normal);
    glVertexAttribPointer(a.normal, 3, GL_FLOAT, GL_FALSE, elementSize, offset);

	// Draw!
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawable.indexBuffer);
    glDrawElements(GL_TRIANGLES, drawable.indexCount, GL_UNSIGNED_SHORT, 0);
    
	// Restore previous state after we're done
    glDisableVertexAttribArray(a.position);
    glDisableVertexAttribArray(a.normal);
}

//void RenderingEngine::updateAnimation(double timeStep) {
//	// Constants
//	static const float duration = 0.5f;
//
//	// Don't change anything if the animation is finished
//    if (animation.current == animation.end) {
//        return;
//	}
//    
//	// Advance the animation
//    animation.elapsed += timeStep;
//    if (animation.elapsed >= duration) {
//		std::cout << "Animation finished" << std::endl;
//		// Set the current direction to be exactly the end direction
//        animation.current = animation.end;
//    } else {
//        float mu = animation.elapsed / duration;
//		// Calculate intermediary direction
//        animation.current = animation.start.Slerp(mu, animation.end);
//    }
//}
//
//// Expects the direction to rotate to
//void RenderingEngine::rotate(vec3 direction) {
//	std::cout << "Animation started" << std::endl;
//    animation.elapsed = 0;
//    animation.start = animation.current;
//    animation.end = Quaternion::CreateFromVectors(vec3(0, 1, 0), direction);
//}
