#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class GLWindow : public QOpenGLWindow, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    GLWindow();
    ~GLWindow();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    void initShaders();
    void initTextures();

private:
    QOpenGLShaderProgram shaderProgram;
    QOpenGLVertexArrayObject VaoObj;
    QOpenGLBuffer VboBuf, IboBuf;

    QOpenGLTexture *texture;
};

#endif // GLWINDOW_H
