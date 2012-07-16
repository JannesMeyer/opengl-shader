// Interface to the OpenGL renderer
class IRenderingEngine {
public:
    virtual void render() const = 0;
    //virtual void updateAnimation(float timeStep) = 0;
};