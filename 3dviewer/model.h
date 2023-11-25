#ifndef MODEL_H
#define MODEL_H
#include <vector>

#include <QVector4D>
#include <QVector3D>
#include <QMatrix4x4>
#include <QString>
#include <QFile>
#include <QTextStream>

class Model
{
public:
    Model();
    ~Model() = default;

    unsigned numVertices{0};
    unsigned numFaces{0};

    std::vector<QVector4D> vertices;
    unsigned vboVertices{0};
    unsigned vao{0};

    std::vector<unsigned int> indices;
    unsigned eboIndices{0};

    void readOFFFile(const QString &);

    QVector3D centroidBB, minBB, maxBB;
    float diagonalBB{0};
    void computeBBox();
    void rescaleModel();

    std::vector<QString> vertexShaderFile = {":/shaders/vzdepth.glsl"};
    std::vector<QString> fragmentShaderFile = {":/shaders/fzdepth.glsl"};
    std::vector<unsigned> shaderProgram;
    int currentShader{0};

    // Representa a matriz de transformação usada no shader
    QMatrix4x4 modelMatrix;
};
#endif
