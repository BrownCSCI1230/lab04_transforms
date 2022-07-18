#include "axes.h"
#include "glrenderer.h"
#include "glm/gtc/constants.hpp"
#include "glm.hpp"

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

void pushVec3(glm::vec3 vec, std::vector<float> &data) {
    data.push_back(vec.x);
    data.push_back(vec.y);
    data.push_back(vec.z);
}

void initializeConeData(std::vector<float> &data) {
    const int THETA_TESSELATIONS = 10;

    glm::vec3 p1 = glm::vec3(0,0,1);
    for(int i = 0; i < THETA_TESSELATIONS; i++) {
        float the1 = 1.0 * i / THETA_TESSELATIONS * 2 * glm::pi<float>();
        float the2 = 1.0 * (i + 1) / THETA_TESSELATIONS * 2 * glm::pi<float>();

        glm::vec3 p2 = glm::vec3(sin(the1),cos(the1),0);
        glm::vec3 p3 = glm::vec3(sin(the2),cos(the2),0);

        pushVec3(p1,data);
        pushVec3(p2,data);
        pushVec3(p3,data);
    }
}

void Axes::init(GLRenderer* context) {

    // Axis buffer generation
    context->glGenBuffers(1, &m_axesVbo);
    context->glBindBuffer(GL_ARRAY_BUFFER, m_axesVbo);
    std::vector<GLfloat> axes{0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f};
    context->glBufferData(GL_ARRAY_BUFFER, axes.size() * sizeof(GLfloat), axes.data(), GL_STATIC_DRAW);

    // Axis VAO generation
    context->glGenVertexArrays(1, &m_axesVao);
    context->glBindVertexArray(m_axesVao);

    context->glEnableVertexAttribArray(0);
    context->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void*>(0));

    context->glBindBuffer(GL_ARRAY_BUFFER, 0);
    context->glBindVertexArray(0);


    // Arrow buffer generation
    context->glGenBuffers(1, &m_arrowVbo);
    context->glBindBuffer(GL_ARRAY_BUFFER, m_arrowVbo);
    initializeConeData(coneData);
    context->glBufferData(GL_ARRAY_BUFFER, coneData.size() * sizeof(GLfloat), coneData.data(), GL_STATIC_DRAW);

    // Arrow VAO generation
    context->glGenVertexArrays(1, &m_arrowVao);
    context->glBindVertexArray(m_arrowVao);

    context->glEnableVertexAttribArray(0);
    context->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void*>(0));

    context->glBindBuffer(GL_ARRAY_BUFFER, 0);
    context->glBindVertexArray(0);


}

void Axes::draw(GLRenderer* context) {

    //Draw Axes
    context->glUseProgram(context->m_axesshader);
    context->glBindVertexArray(m_axesVao);

    //set model and color uniforms
    context->glUniformMatrix4fv(context->glGetUniformLocation(context->m_axesshader,"model"),
                                1,GL_FALSE,&m_model[0][0]);
    context->glUniform3fv(context->glGetUniformLocation(context->m_axesshader,"inColor"),
                                1,&m_color[0]);

    context->glLineWidth(4);

    context->glDrawArrays(GL_LINES, 0, 6);

    context->glBindVertexArray(0);
    context->glUseProgram(0);

    //Draw Arrows
    context->glUseProgram(context->m_arrowshader);
    context->glBindVertexArray(m_arrowVao);

    //set model and color uniforms
    context->glUniformMatrix4fv(context->glGetUniformLocation(context->m_arrowshader,"model"),
                                1,GL_FALSE,&m_model[0][0]);
    context->glUniform3fv(context->glGetUniformLocation(context->m_arrowshader,"inColor"),
                                1,&m_color[0]);

    //set offset axis uniform
    glm::vec3 coneAxis = glm::vec3(1,0,0);
    context->glUniform3fv(context->glGetUniformLocation(context->m_arrowshader,"offsetAxis"),
                                1,&coneAxis[0]);
    //draw
    context->glDrawArrays(GL_TRIANGLES, 0, coneData.size() / 3);


    //set offset axis uniform
    coneAxis = glm::vec3(0,1,0);
    context->glUniform3fv(context->glGetUniformLocation(context->m_arrowshader,"offsetAxis"),
                                1,&coneAxis[0]);
    //draw
    context->glDrawArrays(GL_TRIANGLES, 0, coneData.size() / 3);


    //set offset axis uniform
    coneAxis = glm::vec3(0,0,1);
    context->glUniform3fv(context->glGetUniformLocation(context->m_arrowshader,"offsetAxis"),
                                1,&coneAxis[0]);
    //draw
    context->glDrawArrays(GL_TRIANGLES, 0, coneData.size() / 3);

    context->glBindVertexArray(0);
    context->glUseProgram(0);


}
