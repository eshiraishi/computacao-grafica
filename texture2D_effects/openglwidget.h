#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QTimer>
#include <QVector4D>
#include <QFile>
#include <QKeyEvent>
#include <QApplication>
#include <QImage>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    GLuint vboVertices{0};
    GLuint vboColors{0};
    GLuint eboIndices{0};
    GLuint vao{0};

    // objeto de armazenamento dos vértices das coordenadas de texturas na GPU
    GLuint vboTextCoords{0};

    // identificador da textura sendo usada atualmente na pipeline
    GLuint textureID{0};

    std::vector<QVector4D> vertices;
    std::vector<QVector4D> colors;
    std::vector<GLuint> indices;

    // coordenadas posicionais da textura em 2D
    std::vector<QVector2D> textCoords;

    GLuint shaderProgram{0};

    void createVBOs();
    void createShaders();

    void destroyVBOs();
    void destroyShaders();

    void changeDiagonal();

    void keyPressEvent(QKeyEvent *event) override;

    // metodo usado para inicializacao dos atributos da textura
    void loadTexture();


signals:

public slots:
    void toggleDarkMode(bool);
    void selectShaderEffect(int);

private:

};

#endif // OPENGLWIDGET_H
