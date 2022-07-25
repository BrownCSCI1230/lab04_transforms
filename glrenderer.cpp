#include "glrenderer.h"

#include <QCoreApplication>
#include <QOpenGLShaderProgram>
#include "CS1230Lib/shaderloader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "transforms.h"
#include <QMouseEvent>
#include <glm/gtx/string_cast.hpp>

GLRenderer::GLRenderer(QWidget *parent)
    : QOpenGLWidget(parent)
{

}

GLRenderer::~GLRenderer()
{
    makeCurrent();
    doneCurrent();
}

void GLRenderer::initializeGL()
{
    // Setting up OpenGL for Qt Creator //
    initializeOpenGLFunctions();

    m_zoom = 2.2;
    m_angleX = 2;
    m_angleY = -1.7;
    rebuildMatrices();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);

    //load shaders
    ShaderLoader loader;
    m_gridshader = loader.createShaderProgram("Resources/Shaders/grid.vert", "Resources/Shaders/grid.frag"); //Shader setup (DO NOT EDIT)
    m_axesshader = loader.createShaderProgram("Resources/Shaders/axes.vert", "Resources/Shaders/axes.frag"); //Shader setup (DO NOT EDIT)
    m_arrowshader = loader.createShaderProgram("Resources/Shaders/arrow.vert", "Resources/Shaders/arrow.frag"); //Shader setup (DO NOT EDIT)

    //initialize axis objects
    m_student.init(this, glm::mat4(1), glm::vec3(1, 1, 1));
    glm::mat4 m1 = glm::translate(glm::vec3(4, 4, 0)) * glm::rotate(30.f, glm::vec3(0, 0, 1)) * glm::translate(glm::vec3(0, -1, 0)) * glm::scale(glm::vec3(2, -2, 1));
    std::cout << glm::to_string(m1) << std::endl;
    m_obj1.init(this, m1,
                glm::vec3(153.f/255.f, 221.f/255.f, 255.f/255.f));
    m_obj2.init(this, glm::mat4(    0.612372, 0.353553, -0.707107, 0.000000,
                                   -0.500000, 0.866025, 0.000000, 0.000000,
                                    0.612372, 0.353553, 0.707107, 0.000000,
                                    4.000000, 4.000000, 0.000000, 1.000000),
                glm::vec3(187.f/255.f, 204.f/255.f, 51.f/255.f));
    m_obj3.init(this, glm::mat4(    0.500000, 0.000000, 0.000000, 0.000000,
                                    0.000000, 0.433013, 0.250000, 0.000000,
                                    0.000000, -0.250000, 0.433013, 0.000000,
                                    3.000000, 1.000000, 6.000000, 1.000000),
                glm::vec3(238.f/255.f, 136.f/255.f, 102.f/255.f));
    m_cam.init(this, glm::mat4(1), glm::vec3(255.f/255.f, 170.f/255.f, 187.f/255.f));

    //initialize grid
    m_grid.init(this);
}

void GLRenderer::paintGL()
{
    //clear the frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Set view and projection matricies in all shaders
    glUseProgram(m_axesshader);
    glUniformMatrix4fv(glGetUniformLocation(m_axesshader,"view"),
                       1,GL_FALSE,&m_view[0][0]);

    glUniformMatrix4fv(glGetUniformLocation(m_axesshader,"proj"),
                       1,GL_FALSE,&m_projection[0][0]);
    glUseProgram(0);

    glUseProgram(m_gridshader);
    glUniformMatrix4fv(glGetUniformLocation(m_gridshader,"view"),
                       1,GL_FALSE, &m_view[0][0]);

    glUniformMatrix4fv(glGetUniformLocation(m_gridshader,"proj"),
                       1,GL_FALSE,&m_projection[0][0]);
    glUseProgram(0);

    glUseProgram(m_arrowshader);
    glUniformMatrix4fv(glGetUniformLocation(m_arrowshader,"view"),
                       1,GL_FALSE, &m_view[0][0]);

    glUniformMatrix4fv(glGetUniformLocation(m_arrowshader,"proj"),
                       1,GL_FALSE,&m_projection[0][0]);
    glUseProgram(0);


    //Draw Gridlines
    m_grid.draw(this);

    //Draw Axes
    m_obj1.draw(this);
    m_obj2.draw(this);
    m_obj3.draw(this);
    m_cam.draw(this);
    m_student.draw(this);
}

void GLRenderer::resizeGL(int w, int h)
{
    rebuildMatrices();
}

void GLRenderer::buttonPressed(Button button) {
    switch(button) {
        case Button::OBJECT1:
            m_student.applyTransform(Transforms::getObj1Matrix());
            break;
        case Button::OBJECT2:
            m_student.applyTransform(Transforms::getObj2Matrix());
            break;
        case Button::OBJECT3:
            m_student.applyTransform(Transforms::getObj3Matrix());
            break;
        case Button::VIEW:
            m_student.applyTransform(Transforms::getViewMatrix(glm::vec3(), glm::vec3(), glm::vec3()));
            break;
        case Button::RESET:
            m_student.reset();
            break;
    }

    update();
}

//---------------------------------------//
// Camera Movement, Don't worry about it //
//---------------------------------------//

void GLRenderer::mousePressEvent(QMouseEvent *event) {
    // Set initial mouse position
    m_prevMousePos = event->pos();
}

void GLRenderer::mouseMoveEvent(QMouseEvent *event) {
    // update angle member variables based on event parameters
    m_angleX += 10 * (event->position().x() - m_prevMousePos.x()) / (float) width();
    m_angleY += 10 * (event->position().y() - m_prevMousePos.y()) / (float) height();
    m_prevMousePos = event->pos();
    rebuildMatrices();
}

void GLRenderer::wheelEvent(QWheelEvent *event) {
    // update zoom based on event parameter
    m_zoom -= event->angleDelta().y() / 200.f;
    rebuildMatrices();
}

void GLRenderer::rebuildMatrices() {
    // update view matrix by rotating eye vector based on x and y angles
    m_view = glm::mat4(1);
    glm::mat4 rot = glm::rotate(-10 * m_angleX,glm::vec3(0,0,1));
    glm::vec3 eye = glm::vec3(5, 5, 5);
    eye = glm::vec3(rot * glm::vec4(eye,1));

    rot = glm::rotate(-10 * m_angleY,glm::cross(glm::vec3(0,0,1),eye));
    eye = glm::vec3(rot * glm::vec4(eye,1));

    eye = eye * m_zoom;

    m_view = glm::lookAt(eye,glm::vec3(0,0,0),glm::vec3(0,0,1));

    m_projection = glm::perspective(45.0,1.0 * width() / height(),0.01,100.0);

    update();
}

