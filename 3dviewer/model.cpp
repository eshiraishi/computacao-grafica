#include "model.h"

Model::Model()
{
    shaderProgram.resize(fragmentShaderFile.size());
}

void Model::readOFFFile(const QString &fileName)
{
    QFile data(fileName);
    data.open(QFile::ReadOnly);

    if (!data.isOpen())
    {
        qWarning("Não conseguiu abrir");
        return;
    }

    QTextStream stream(&data);
    QString notUsed;
    stream >> notUsed;
    stream >> numVertices >> numFaces >> notUsed;
    vertices.resize(numVertices);
    indices.resize(numFaces * 3);

    float x, y, z;
    for (size_t i{0}; i < numVertices; ++i)
    {
        stream >> x >> y >> z;
        vertices[i] = QVector4D(x, y, z, 1);
    }

    unsigned a, b, c;
    for (size_t i{0}; i < numFaces; ++i)
    {
        stream >> notUsed >> a >> b >> c;
        indices[i * 3 + 0] = a;
        indices[i * 3 + 1] = b;
        indices[i * 3 + 2] = c;
    }

    data.close();
}

void Model::computeBBox()
{
    auto minLim = std::numeric_limits<float>::lowest();
    auto maxLim = std::numeric_limits<float>::max();

    maxBB = QVector3D(minLim, minLim, minLim);
    minBB = QVector3D(maxLim, maxLim, maxLim);

    for (size_t i{0}; i < numVertices; i++)
    {
        maxBB.setX(std::max(maxBB.x(), vertices[i].x()));
        maxBB.setY(std::max(maxBB.y(), vertices[i].y()));
        maxBB.setZ(std::max(maxBB.z(), vertices[i].z()));

        minBB.setX(std::min(minBB.x(), vertices[i].x()));
        minBB.setY(std::min(minBB.y(), vertices[i].y()));
        minBB.setZ(std::min(minBB.z(), vertices[i].z()));
    }
    centroidBB = 0.5 * (maxBB + minBB);
    diagonalBB = (maxBB - minBB).length();
}

void Model::rescaleModel()
{
    computeBBox();
    float invdiag{2.5f / diagonalBB};
    modelMatrix.scale(invdiag, invdiag, invdiag);
    modelMatrix.translate(-centroidBB);
}
