#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

class Camera
{
public:
    Camera();
    // posição da camera na cena
    QVector3D eye{QVector3D(0,0,2)};
    // ponto onde a camera está olhando
    QVector3D center{QVector3D(0,0,0)};
    // direção da câmera
    QVector3D up{QVector3D(0,1,0)};
    // propriedades da camera no espaço
    QMatrix4x4 viewMatrix;
    // propriedades de projeção do objeto de 3D para 2D
    QMatrix4x4 projectionMatrix;
    // inicializa viewMatrix no construtor da classe
    void createViewMatrix();
    // redimensiona a proporção da imagem a partir da janela e permite mudar a proporção entre perspectiva e ortográfica
    void resizeViewPort(int width, int height, bool ortho=false);
};

#endif
