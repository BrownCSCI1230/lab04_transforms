#ifndef GRIDLINES_H
#define GRIDLINES_H

#include "glm.hpp"
#include <GL/gl.h>
#include <vector>

//Forward Declaration of glrenderer
class GLRenderer;

class Gridlines
{
public:
    Gridlines();

    void init(GLRenderer* context);
    void draw(GLRenderer* context);

private:
    std::vector<float> lineData;
    glm::mat4 m_model;
    glm::vec3 m_color;
    GLuint m_vbo;
    GLuint m_vao;
};

#endif // GRIDLINES_H
