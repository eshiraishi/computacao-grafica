#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <memory>

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QTimer>
#include <QVector4D>
#include <QFile>
#include <QKeyEvent>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <model.h>
#include <camera.h>
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public slots:
    void toggleWireframe(bool);
    void toggleOrthographic(bool);
    void toggleDarkMode(bool);
    void showFileOpenDialog();
public:
    Camera camera;
    bool wireframe{false};
    bool orthographic{false};

    explicit OpenGLWidget(QWidget *parent = nullptr);
    void initializeGL() override;
    void paintGL() override;
    std::vector<QVector4D> vertices;
    GLuint vboVertices{0};
    GLuint vao{0};

    std::vector<QVector4D> colors;
    GLuint vboColors{0};

    std::vector<GLuint> indices;
    GLuint eboIndices{0};

    GLuint shaderProgram{0};

    std::shared_ptr<Model> model;

    void createVBOs(std::shared_ptr<Model>);
    void createShaders(std::shared_ptr<Model>);

    void destroyVBOs(std::shared_ptr<Model>);
    void destroyShaders(std::shared_ptr<Model>);
    ~OpenGLWidget();

    void resizeGL(int w, int h) override;
    void keyPressEvent(QKeyEvent *event) override;
signals:
    void statusBarMessage(QString);

private:
};

#endif
