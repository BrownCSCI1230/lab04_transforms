#include "glrenderer.h"

#include <QCoreApplication>
#include "CS1230Lib/resourceloader.h"

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

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    m_shader = ResourceLoader::createShaderProgram("Resources/Shaders/default.vert", "Resources/Shaders/default.frag"); //Shader setup (DO NOT EDIT)

    // Vertex Buffer Objects //

    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    std::vector<GLfloat> triangle{-0.5f, 1.0f,  0.5f, 1.0f, 0.0f, 0.0f,
                                  -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
                                   0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f};
\
    glBufferData(GL_ARRAY_BUFFER, triangle.size() * sizeof(GLfloat), triangle.data(), GL_STATIC_DRAW);

    // Vertex Array Objects //

    glGenVertexArrays(1, &m_vao);

    glBindVertexArray(m_vao);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

    // Returning to Default State //

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // TODO: replace triangle with initialization of axes and gridlines
}

void GLRenderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_shader);

    glBindVertexArray(m_vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);

    glUseProgram(0);

    // TODO: loop through objects and draw
}

void GLRenderer::resizeGL(int w, int h)
{

}
