#ifndef AXES_H
#define AXES_H

#include "glm.hpp"
#include <GL/gl.h>
#include <vector>


//Forward Declaration of glrenderer
class GLRenderer;

class Axes
{
public:
    Axes();
    Axes(glm::mat4 model, glm::vec3 color);

    void applyTransform(glm::mat4 transform);

    void init(GLRenderer* context);
    void draw(GLRenderer* context);

private:
    std::vector<float> lineData;
    glm::mat4 m_model;
    glm::vec3 m_color;
    GLuint m_vbo;
    GLuint m_vao;
};

#endif // AXES_H
