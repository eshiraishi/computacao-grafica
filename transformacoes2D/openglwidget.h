#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QtOpenGLWidgets/QOpenGLWidget> // herda a janela e substituiu o QWidget
#include <QOpenGLExtraFunctions>         //inserido - herda as funções do OpenGL
#include <QTimer>
#include <QVector4D>
#include <QMatrix4x4>
#include <QFile>
#include <QKeyEvent>
#include <QApplication>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions // substitui a heranca do QWidget
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    QMatrix4x4 mModel;

    GLuint vboVertices{0};
    GLuint vboVerticesAxis{0};
    GLuint vboColors{0};
    GLuint eboIndices{0};
    GLuint vao{0};
    GLuint vaoAxis{0};

    std::vector<QVector4D> vertices;
    std::vector<QVector4D> colors;
    std::vector<GLuint> indices;
    QTimer timer;
    GLuint shaderProgram{0};

    void createVBOs();
    void createShaders();

    void destroyVBOs();
    void destroyShaders();

    void changeDiagonal();

    void keyPressEvent(QKeyEvent *event) override;

    void rotationCentroidExample();
    void rotationOrbitExample();
    void scaleExample();
    void nonComutativeExample();
    void drawAxis();

signals:
public slots:
    void toggleDarkMode(bool);

private:
};

#endif // OPENGLWIDGET_H
