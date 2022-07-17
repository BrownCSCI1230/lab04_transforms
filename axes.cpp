#include "axes.h"
#include "glrenderer.h"

Axes::Axes() {

}

Axes::Axes(glm::mat4 model, glm::vec3 color)
{
    m_model = model;
    m_color = color;
}

void Axes::applyTransform(glm::mat4 transform) {
    m_model = transform;
    // TODO: update
}

void Axes::init(GLRenderer* context) {

    // Vertex Buffer Objects //

    context->glGenBuffers(1, &m_vbo);

    context->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    std::vector<GLfloat> axes{0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f};
\
    context->glBufferData(GL_ARRAY_BUFFER, axes.size() * sizeof(GLfloat), axes.data(), GL_STATIC_DRAW);

    // Vertex Array Objects //

    context->glGenVertexArrays(1, &m_vao);

    context->glBindVertexArray(m_vao);

    context->glEnableVertexAttribArray(0);
    context->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void*>(0));

    // Returning to Default State //
    context->glBindBuffer(GL_ARRAY_BUFFER, 0);
    context->glBindVertexArray(0);

}

void Axes::draw(GLRenderer* context) {
    // TODO: draw axes

    context->glBindVertexArray(m_vao);

    //todocolor
    context->glUniformMatrix4fv(context->glGetUniformLocation(context->m_axesshader,
                                                              "model"),
                                1,GL_FALSE,
                                &m_model[0][0]);

    context->glUniform3fv(context->glGetUniformLocation(context->m_axesshader,
                                                        "inColor"),
                                1,
                                &m_color[0]);

    context->glLineWidth(4);
    context->glDrawArrays(GL_LINES, 0, 6);

    context->glBindVertexArray(0);
}
