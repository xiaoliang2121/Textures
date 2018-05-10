#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QKeyEvent>
#include <QBasicTimer>

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
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    void initShaders();
    void initTextures();
    float radians(float x);

private:
    QOpenGLShaderProgram shaderProgram;
    QOpenGLVertexArrayObject VaoObj;
    QOpenGLBuffer VboBuf, IboBuf;

    QOpenGLTexture *texture;
    QOpenGLTexture *texture1;

    GLfloat alpha;
    float angles;
    QMatrix4x4 transform;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    QVector3D camPos;
    QVector3D camFront;
    QVector3D camUp;
    QVector2D mousePressPos;
    float yaw;
    float pitch;
    float fov;

    QBasicTimer timer;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;
};

#endif // GLWINDOW_H
