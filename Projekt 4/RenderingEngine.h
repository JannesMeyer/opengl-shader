#pragma once

#include "IRenderingEngine.h"

#include <gl/glew.h>

static const float RevolutionsPerSecond = 1;

class RenderingEngine : public IRenderingEngine {
private:
    float currentAngle;
    GLuint simpleProgram;
    GLuint framebuffer;
    GLuint renderbuffer;

    GLuint buildShader(const char* source, GLenum shaderType) const;
    GLuint buildProgram(const char* vShader, const char* fShader) const;
    void applyOrtho(float maxX, float maxY) const;
    void applyRotation(float degrees) const;

public:
    RenderingEngine(int width, int height);
    void render() const;
    void updateRotation(float rotation);
};