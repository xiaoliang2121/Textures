#include "glwindow.h"

GLWindow::GLWindow():
    IboBuf(QOpenGLBuffer::IndexBuffer)
{
}

GLWindow::~GLWindow()
{
    makeCurrent();
    VboBuf.destroy();
    IboBuf.destroy();
    doneCurrent();
}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.7f,0.7f,0.7f,1.0f);

    initShaders();
    initTextures();
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLWindow::initShaders()
{
    if(!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/triangle.vert"))
    {
        qDebug()<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<shaderProgram.log()<<endl;
    }
    if(!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/triangle.frag"))
    {
        qDebug()<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<shaderProgram.log()<<endl;
    }

    if(!shaderProgram.link())
    {
        qDebug()<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<shaderProgram.log()<<endl;
    }
}

void GLWindow::initTextures()
{

}
