// Interface to the renderer
class IRenderingEngine {
public:
    virtual void render() const = 0;
    virtual void updateAnimation(double timeStep) = 0;
};