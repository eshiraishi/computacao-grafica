#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <QVector4D>
#include <QVector3D>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMatrix4x4>
#include <material.h>
#include <QVector2D>
#include <cmath>

class Model
{
public:
    Model();
    ~Model() = default;

    std::vector<QVector4D> vertices;
    std::vector<unsigned> indices;

    // vector de vetores do QT: representação na cpu pré-binding
    // vbo: representação na gpu pos binding
    // Lower / upper: mix de texturas no shader

    // Para cilinder mapping:
    std::vector<QVector2D> textureCoords;
    unsigned vboTextCoords{0};
    void createTextCoords();
    unsigned textureID{0};
    unsigned textureIDLayerLower{0};
    unsigned textureIDLayerUpper{0};

    // Para normal mapping:

    // vetores normais
    std::vector<QVector3D> normals;
    unsigned vboNormals{0};
    void createNormals();
    unsigned textureIDNormalMapColor{0};
    unsigned textureIDNormalMapNormals{0};

    // vetores tangentes
    std::vector<QVector4D> tangents;
    unsigned vboTangents{0};
    void createTangents();

    unsigned numVertices{0};
    unsigned numFaces{0};

    unsigned vao{0};
    unsigned vboVertices{0};
    unsigned eboIndices{0};

    // Para cube mapping
    unsigned textureIDCubeMap{0};

    void readOFFFile(const QString &);

    void computeBBox();
    void rescaleModelMatrix();
    QVector3D centroidBB, minBB, maxBB;
    float diagonalBB{0.0f};
    QMatrix4x4 modelMatrix;

    int currentShader{0};

    std::vector<QString> vertexShaderFileName   = {":/shaders/vzdepth.glsl",
                                                   ":/shaders/vnormal.glsl",
                                                   ":/shaders/vflat.glsl",
                                                   ":/shaders/vgouraud.glsl",
                                                   ":/shaders/vphong.glsl",
                                                   ":/shaders/vtexture.glsl",
                                                   ":/shaders/vtexturelayers.glsl",
                                                   ":/shaders/vnormalmap.glsl",
                                                   ":/shaders/vcubemap.glsl"};

    std::vector<QString> fragmentShaderFileName = {":/shaders/fzdepth.glsl",
                                                   ":/shaders/fnormal.glsl",
                                                   ":/shaders/fflat.glsl",
                                                   ":/shaders/fgouraud.glsl",
                                                   ":/shaders/fphong.glsl",
                                                   ":/shaders/ftexture.glsl",
                                                   ":/shaders/ftexturelayers.glsl",
                                                   ":/shaders/fnormalmap.glsl",
                                                   ":/shaders/fcubemap.glsl"};
    std::vector<unsigned> shaderProgram;

    Material material;
};

#endif // MODEL_H
