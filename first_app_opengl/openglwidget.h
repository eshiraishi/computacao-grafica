#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QTimer>

#include <QtOpenGLWidgets/QOpenGLWidget> // herda a janela e substituiu o QWidget
#include <QOpenGLExtraFunctions> //inserido - herda as funções do OpenGL

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions // substitui a heranca do QWidget
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
public slots:
    void toggleDarkMode(bool);
private:
    QTimer timer;
    bool blinkFlag{false};
signals:

};

#endif // OPENGLWIDGET_H
