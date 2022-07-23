#include "gridlines.h"
#include "glrenderer.h"
#include "glm/gtx/transform.hpp"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Gridlines::Gridlines()
{

}


void Gridlines::init(GLRenderer* context) {
    // Vertex Buffer Objects //

    context->glGenBuffers(1, &m_vbo);

    context->glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    int gridSize = 20;
    int numLines = gridSize * gridSize + gridSize * 2;

    lineData.reserve(numLines * 6);

    for(int x = 0; x < gridSize; x++) {
        for(int y = 0; y < gridSize; y++) {
            //bottom
            lineData.push_back(x);
            lineData.push_back(y);
            lineData.push_back(0);

            lineData.push_back(x+1);
            lineData.push_back(y);
            lineData.push_back(0);

            //right
            lineData.push_back(x+1);
            lineData.push_back(y);
            lineData.push_back(0);

            lineData.push_back(x+1);
            lineData.push_back(y+1);
            lineData.push_back(0);


            if(x == 0) {
                //left
                lineData.push_back(x);
                lineData.push_back(y);
                lineData.push_back(0);

                lineData.push_back(x);
                lineData.push_back(y+1);
                lineData.push_back(0);
            }

            if(y == gridSize - 1) {
                //top
                lineData.push_back(x);
                lineData.push_back(y+1);
                lineData.push_back(0);

                lineData.push_back(x+1);
                lineData.push_back(y+1);
                lineData.push_back(0);
            }
        }
    }

    context->glBufferData(GL_ARRAY_BUFFER, lineData.size() * sizeof(GLfloat), lineData.data(), GL_STATIC_DRAW);

    // Vertex Array Objects //

    context->glGenVertexArrays(1, &m_vao);

    context->glBindVertexArray(m_vao);

    context->glEnableVertexAttribArray(0);
    context->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void*>(0));

    // Returning to Default State //
    context->glBindBuffer(GL_ARRAY_BUFFER, 0);
    context->glBindVertexArray(0);
}


void Gridlines::draw(GLRenderer* context) {

    context->glUseProgram(context->m_gridshader);


    context->glBindVertexArray(m_vao);

    context->glLineWidth(1);

    //draw xy plane
    m_model = glm::mat4(1);
    context->glUniformMatrix4fv(context->glGetUniformLocation(context->m_gridshader,
                                                              "model"),
                                1,GL_FALSE,
                                &m_model[0][0]);
    context->glDrawArrays(GL_LINES, 0, lineData.size());

    //draw xz plane
    m_model = glm::rotate(90.0f,glm::vec3(1.0,0.0,0.0));
    context->glUniformMatrix4fv(context->glGetUniformLocation(context->m_gridshader,
                                                              "model"),
                                1,GL_FALSE,
                                &m_model[0][0]);
    context->glDrawArrays(GL_LINES, 0, lineData.size());

    //draw yz plane
    m_model = glm::rotate(-90.0f,glm::vec3(0.0,1.0,0.0));
    context->glUniformMatrix4fv(context->glGetUniformLocation(context->m_gridshader,
                                                              "model"),
                                1,GL_FALSE,
                                &m_model[0][0]);
    context->glDrawArrays(GL_LINES, 0, lineData.size());

    context->glBindVertexArray(0);

    context->glUseProgram(0);
}
