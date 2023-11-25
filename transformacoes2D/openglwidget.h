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

    // Representa as matrizes de transformação a cada animação
    QMatrix4x4 mModel;
    // Para controlar a taxa de atualização das animações
    QTimer timer;
    // usados para definir e desenhar os eixos
    GLuint vboVerticesAxis{0};
    GLuint vaoAxis{0};

    GLuint shaderProgram{0};
    GLuint vboVertices{0};
    GLuint vboColors{0};
    GLuint eboIndices{0};
    GLuint vao{0};

    std::vector<QVector4D> vertices;
    std::vector<QVector4D> colors;
    std::vector<GLuint> indices;

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

#endif
