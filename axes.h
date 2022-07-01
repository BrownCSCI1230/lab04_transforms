#ifndef AXES_H
#define AXES_H

#include "glm.hpp"

class Axes
{
public:
    Axes(glm::mat4 model, glm::vec3 color);

    void applyTransform(glm::mat4 transform);
    void draw();

private:
    glm::mat4 m_model;
    glm::vec3 m_color;
};

#endif // AXES_H
