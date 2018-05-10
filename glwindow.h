#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QKeyEvent>

class GLWindow : public QOpenGLWindow, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    GLWindow();
    ~GLWindow();

protected slots:


protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent *event) override;

private:
    void initShaders();
    void initTextures();

private:
    QOpenGLShaderProgram shaderProgram;
    QOpenGLVertexArrayObject VaoObj;
    QOpenGLBuffer VboBuf, IboBuf;

    QOpenGLTexture *texture;
    QOpenGLTexture *texture1;

    GLfloat alpha;
    float angles;
    float rotateAngles;
    QMatrix4x4 transform;
    QMatrix4x4 view;
    QMatrix4x4 projection;
    QVector<QVector3D> cubePositions;

    QVector3D camPos;
    QVector3D camFront;
    QVector3D camUp;
};

#endif // GLWINDOW_H
