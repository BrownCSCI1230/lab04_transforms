#include "glrenderer.h"

#include <QCoreApplication>
#include "CS1230Lib/resourceloader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

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
    QSurfaceFormat fmt;
    fmt.setVersion(3, 1);
    QOpenGLContext::currentContext()->setFormat(fmt);
    initializeOpenGLFunctions();

    constructViewProjectionMatricies();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_LINE_SMOOTH);

    //load shaders
    m_gridshader = ResourceLoader::createShaderProgram("Resources/Shaders/grid.vert", "Resources/Shaders/grid.frag"); //Shader setup (DO NOT EDIT)
    m_axesshader = ResourceLoader::createShaderProgram("Resources/Shaders/axes.vert", "Resources/Shaders/axes.frag"); //Shader setup (DO NOT EDIT)

    //initialize axis objects
    m_obj1 = Axes(glm::mat4(1), glm::vec3(0.9,1,0.9));
    m_obj1.init(this);

    m_obj2 = Axes(glm::rotate(glm::translate(glm::mat4(1),
                                             glm::vec3(5,5,5)),
                              60.0f,
                              glm::vec3(0,1,0)),
                  glm::vec3(1,0.6,0.2));

    m_obj2.init(this);

    //initialize grid
    m_grid.init(this);

}

void GLRenderer::paintGL()
{
    //clear the frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //Draw Gridlines
    glUseProgram(m_gridshader);

    glUniformMatrix4fv(glGetUniformLocation(m_gridshader,
                                            "view"),
                       1,GL_FALSE,
                       &m_view[0][0]);

    glUniformMatrix4fv(glGetUniformLocation(m_gridshader,
                                            "proj"),
                       1,GL_FALSE,
                       &m_projection[0][0]);

    m_grid.draw(this);

    glUseProgram(0);


    //Draw Axes
    glUseProgram(m_axesshader);

    glUniformMatrix4fv(glGetUniformLocation(m_axesshader,
                                            "view"),
                       1,GL_FALSE,
                       &m_view[0][0]);

    glUniformMatrix4fv(glGetUniformLocation(m_axesshader,
                                            "proj"),
                       1,GL_FALSE,
                       &m_projection[0][0]);

    m_obj1.draw(this);
    m_obj2.draw(this);

    glUseProgram(0);
}

void GLRenderer::resizeGL(int w, int h)
{
    constructViewProjectionMatricies();
}

void GLRenderer::constructViewProjectionMatricies() {
    m_view = glm::lookAt(glm::vec3(15,4,5),
                         glm::vec3(0,4,3),
                         glm::vec3(0,0,1));
    m_projection = glm::perspective(45.0,
                                    1.0 * width()/height(),
                                    0.01,
                                    100.0);
}
