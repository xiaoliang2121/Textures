#include "glwindow.h"
#include <QVector3D>
#include <QVector2D>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
    QVector3D vertexColor;
};

GLWindow::GLWindow():
    IboBuf(QOpenGLBuffer::IndexBuffer),
    texture(nullptr),
    texture1(nullptr),
    alpha(0.2f),
    angles(-55.0f),
    transform(),
    view(),
    projection()
{

}

GLWindow::~GLWindow()
{
    makeCurrent();
    VboBuf.destroy();
    IboBuf.destroy();
    delete texture;
    delete texture1;
    doneCurrent();
}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.7f,0.7f,0.7f,1.0f);
    glEnable(GL_DEPTH_TEST);

    initShaders();
    initTextures();

    VertexData vertices[] = {
        {QVector3D(0.5f, 0.5f, 0.0f), QVector2D(1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},       // 右上
        {QVector3D(0.5f, -0.5f, 0.0f), QVector2D(1.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f)},      // 右下
        {QVector3D(-0.5f, -0.5f, 0.0f), QVector2D(0.0f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f)},     // 左下
        {QVector3D(-0.5f, 0.5f, 0.0f), QVector2D(0.0f, 1.0f), QVector3D(1.0f, 1.0f, 0.0f)}       // 左上
    };

    VertexData vertices36[] = {
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(0.5f, -0.5f, -0.5f), QVector2D(1.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(0.5f,  0.5f, -0.5f), QVector2D(1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(0.5f,  0.5f, -0.5f), QVector2D(1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(-0.5f,  0.5f, -0.5f), QVector2D(0.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},

        {QVector3D(-0.5f, -0.5f, 0.5f), QVector2D(0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(0.5f, -0.5f, 0.5f), QVector2D(1.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(0.5f,  0.5f, 0.5f), QVector2D(1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(0.5f,  0.5f, 0.5f), QVector2D(1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(-0.5f,  0.5f, 0.5f), QVector2D(0.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(-0.5f, -0.5f, 0.5f), QVector2D(0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},

        {QVector3D(-0.5f, 0.5f, 0.5f), QVector2D(1.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(-0.5f, 0.5f, -0.5f), QVector2D(1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(-0.5f, -0.5f, 0.5f), QVector2D(0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(-0.5f, 0.5f, 0.5f), QVector2D(1.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},

        {QVector3D(0.5f,  0.5f,  0.5f), QVector2D(1.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(0.5f,  0.5f, -0.5f), QVector2D(1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(0.5f, -0.5f, -0.5f), QVector2D(0.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(0.5f, -0.5f, -0.5f), QVector2D(0.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(0.5f, -0.5f,  0.5f), QVector2D(0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(0.5f,  0.5f,  0.5f), QVector2D(1.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},

        {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D( 0.5f, -0.5f, -0.5f), QVector2D(1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D( 0.5f, -0.5f,  0.5f), QVector2D(1.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D( 0.5f, -0.5f,  0.5f), QVector2D(1.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(-0.5f, -0.5f,  0.5f), QVector2D(0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},

        {QVector3D(-0.5f,  0.5f, -0.5f), QVector2D(0.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D( 0.5f,  0.5f, -0.5f), QVector2D(1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D( 0.5f,  0.5f,  0.5f), QVector2D(1.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D( 0.5f,  0.5f,  0.5f), QVector2D(1.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(-0.5f,  0.5f,  0.5f), QVector2D(0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)},
        {QVector3D(-0.5f,  0.5f, -0.5f), QVector2D(0.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)}
    };

    GLuint indexs[] = {
        2, 1, 0,
        2, 0, 3
    };

    shaderProgram.bind();
    VaoObj.create();
    VaoObj.bind();

    VboBuf.create();
    VboBuf.bind();
    VboBuf.setUsagePattern(QOpenGLBuffer::StaticDraw);
    VboBuf.allocate(vertices36,36*sizeof(VertexData));

    IboBuf.create();
    IboBuf.bind();
    IboBuf.setUsagePattern(QOpenGLBuffer::StaticDraw);
    IboBuf.allocate(indexs,6*sizeof(GLuint));

    shaderProgram.setAttributeBuffer(0,GL_FLOAT,0,3,sizeof(VertexData));
    shaderProgram.setAttributeBuffer(1,GL_FLOAT,sizeof(QVector3D),2,sizeof(VertexData));
    shaderProgram.setAttributeBuffer(2,GL_FLOAT,sizeof(QVector3D)+sizeof(QVector2D),3,sizeof(VertexData));
    shaderProgram.enableAttributeArray(0);
    shaderProgram.enableAttributeArray(1);
    shaderProgram.enableAttributeArray(2);

    shaderProgram.setUniformValue("ourTexture1",0);
    shaderProgram.setUniformValue("ourTexture2",1);
    shaderProgram.setUniformValue("alpha",alpha);

    //transform.translate(QVector3D(0.5f, -0.5f, 0.0f));
    //transform.scale(QVector3D(0.5f, 0.5f, 0.5f));

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram.bind();

    if(!transform.isIdentity())
        transform = QMatrix4x4();
    transform.rotate(angles,QVector3D(0.5f, 1.0f, 0.0f));

    if(!view.isIdentity())
        view = QMatrix4x4();
    view.translate(QVector3D(0.0f, 0.0f, -3.0f));

    if(!projection.isIdentity())
        projection = QMatrix4x4();
    projection.perspective(45.0f,float(width())/height(),0.1f, 100.0f);

    shaderProgram.setUniformValue("view",view);
    shaderProgram.setUniformValue("projection",projection);
    shaderProgram.setUniformValue("transform",transform);
    shaderProgram.setUniformValue("alpha",alpha);

        glActiveTexture(GL_TEXTURE0);
        texture->bind();
        glActiveTexture(GL_TEXTURE1);
        texture1->bind();
            VaoObj.bind();
            //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
            glDrawArrays(GL_TRIANGLES,0,36);
            VaoObj.release();
        texture1->release();
        texture->release();
        shaderProgram.release();
}

void GLWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
    {
        alpha += 0.1f;
        if(alpha > 1.0)
            alpha = 1.0f;
    }

    if(event->key() == Qt::Key_Down)
    {
        alpha -= 0.1f;
        if(alpha < 0.0)
            alpha = 0.0f;
    }

    if(event->key() == Qt::Key_Left)
    {
        angles -= 10.0f;
    }

    if(event->key() == Qt::Key_Right)
    {
        angles += 10.0f;
    }

    update();
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
    // 纹理1
    texture = new QOpenGLTexture(QImage(":/container.jpg").mirrored());

    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    texture->setWrapMode(QOpenGLTexture::Repeat);
    // 纹理2
    texture1 = new QOpenGLTexture(QImage(":/awesomeface.png").mirrored());

    texture1->setMinificationFilter(QOpenGLTexture::Nearest);
    texture1->setMagnificationFilter(QOpenGLTexture::Linear);

    texture1->setWrapMode(QOpenGLTexture::Repeat);
}
