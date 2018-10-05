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

    GLfloat vert[] = {
        -0.5f, -0.5f ,0.0f,
        0.5f,-0.5f, 0.0f,
        0.0f,0.5f,0.0f
    };

    shaderProgram.bind();
    VaoObj.create();
    VaoObj.bind();

    VboBuf.create();
    VboBuf.bind();
    VboBuf.setUsagePattern(QOpenGLBuffer::StaticDraw);
    VboBuf.allocate(vert,9*sizeof(GLfloat));

    shaderProgram.setAttributeBuffer(0,GL_FLOAT,0,3,3*sizeof(GLfloat));
    shaderProgram.enableAttributeArray(0);

    VaoObj.release();
    VboBuf.release();
    shaderProgram.release();
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.bind();
    VaoObj.bind();
    glDrawArrays(GL_TRIANGLES,0,3);

    VaoObj.release();
    shaderProgram.release();
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
