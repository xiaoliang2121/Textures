#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QKeyEvent>
#include <QTimer>

class GLWindow : public QOpenGLWindow, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    GLWindow();
    ~GLWindow();

protected slots:
    void onTimerOut();

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
    QMatrix4x4 transform;
    QTimer *timer;
    float angles;
};

#endif // GLWINDOW_H
