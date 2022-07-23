#ifndef AXES_H
#define AXES_H

#include "glm.hpp"
#include <vector>


//Forward Declaration of glrenderer
class GLRenderer;

class Axes
{
public:
    Axes();

    void applyTransform(glm::mat4 transform);
    void init(GLRenderer* context, glm::mat4 model, glm::vec3 color);
    void draw(GLRenderer* context);
    void reset();

private:
    std::vector<float> coneData;
    glm::mat4 m_model;
    glm::vec3 m_color;
    unsigned int m_axesVbo;
    unsigned int m_axesVao;
    unsigned int m_arrowVbo;
    unsigned int m_arrowVao;
};

#endif // AXES_H
