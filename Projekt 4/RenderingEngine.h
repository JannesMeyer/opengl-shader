#pragma once

#include "ParametrisierteFlaeche.h"
#include "Objects/Kugel.h"
#include "Objects/Torus.h"
#include "Objects/Klein.h"
//#include "Quaternion.hpp"

#include <GL/glew.h>
#include <vector>

/*
 * A structure that contains vertex and index buffer handles of an object
 */
struct Drawable {
    GLuint vertexBuffer;
    GLuint indexBuffer;
    int indexCount;
};

/*
 * Cache all handles
 */
struct UniformHandles {
	// Vertex shader
    GLint Projection;
    GLint Modelview;
    GLint NormalMatrix;

	// Fragment shader
    GLint LightPosition;
    GLint AmbientMaterial;
    GLint DiffuseMaterial;
    GLint SpecularMaterial;
    GLint Shininess;
};

struct AttributeHandles {
	// Vertices
    GLint position;
    GLint normal;
};

struct ProgramHandles {
	// Program
    GLuint program;
    AttributeHandles attributes;
    UniformHandles uniforms;
};

//struct Animation {
//    Quaternion start;
//    Quaternion end;
//    Quaternion current;
//    double elapsed;
//    double duration;
//};

class RenderingEngine {
private:
    // Generate some geometry
	Drawable torus;
    Drawable kugel;
	Drawable klein; // Klein'sche Flasche

	// Program handles
    ProgramHandles p1;

    ivec2 size; // Viewport size

	Drawable createDrawable(const ParametrisierteFlaeche& surface) const;
    void renderDrawable(const Drawable& drawable, const ProgramHandles& program) const;

	GLuint buildShader(const char* source, GLenum shaderType) const;
    //GLuint buildProgram(const char* vShader, const char* fShader) const;
	void buildProgram(const char* vShader, const char* fShader, ProgramHandles& program) const;

public:
    RenderingEngine(int width, int height);
    void render(float theta) const;

	//void updateAnimation(double timeStep);
	//void rotate(vec3 direction);
};