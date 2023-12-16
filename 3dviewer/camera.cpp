#include "camera.h"

Camera::Camera()
{
    createViewMatrix();
}

void Camera::createViewMatrix()
{
    // inicializa com a identidade para não afetar as demais operações
    viewMatrix.setToIdentity();
    // metodo de alto nível que encapsula o cálculo da matriz que representa a câmera no espaço
    viewMatrix.lookAt(eye,center,up);
}

void Camera::resizeViewPort(int width, int height, bool ortho)
{
    projectionMatrix.setToIdentity();
    // determina a razão atual da janela
    auto aspectRatio{static_cast<float>(width)/static_cast<float>(height)};

    if (!ortho)
        // metodo de alto nivel que determina a matriz que realiza a projeção em perspectiva para converter os vértices de 3D para 2D
        projectionMatrix.perspective(60.0f, aspectRatio, 1.0f, 10.0f);
    else
        // metodo de alto nivel que determina a matriz que realiza a projeção ortográfica para converter os vértices de 3D para 2D
        projectionMatrix.ortho(-aspectRatio, aspectRatio, -1, 1, -4, 4);
}
