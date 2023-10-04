#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void OpenGLWidget::initializeGL(){
 initializeOpenGLFunctions();
 glClearColor(1,1,1,1); // limpa a janela (coloca uma cor RGBA)
 // glClearColor(1,0,0,1); // limpa a janela (coloca uma cor RGBA)
 QObject::connect(&timer, &QTimer::timeout,this,[&](){this->update();});
 timer.start(10);
}

void OpenGLWidget::resizeGL(int w, int h){
}

void OpenGLWidget::paintGL(){
 blinkFlag = !blinkFlag;
 if (blinkFlag)
    glClearColor(1,1,1,1);
 else
    glClearColor(0,0,0,1);
 glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWidget::toggleDarkMode(bool changeToDarkMode){
 makeCurrent();
 if(changeToDarkMode)
     glClearColor(0,0,0,1);
 else
    glClearColor(1,1,1,1);
 update();
}
