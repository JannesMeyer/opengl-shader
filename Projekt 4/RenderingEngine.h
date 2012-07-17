#pragma once

#include "IRenderingEngine.h"
#include "Quaternion.hpp"

#include <GL/glew.h>
#include <vector>

struct Vertex {
    vec3 position;
    vec4 color;
};

struct Animation {
    Quaternion start;
    Quaternion end;
    Quaternion current;
    double elapsed;
    double duration;
};

class RenderingEngine : public IRenderingEngine {
private:
	std::vector<Vertex> cone;
    std::vector<Vertex> disk;
    Animation animation;
    GLuint simpleProgram;

    GLuint buildShader(const char* source, GLenum shaderType) const;
    GLuint buildProgram(const char* vShader, const char* fShader) const;

public:
    RenderingEngine(int width, int height);
    void render() const;
    void updateAnimation(double timeStep);
	void rotate(vec3 direction);
};