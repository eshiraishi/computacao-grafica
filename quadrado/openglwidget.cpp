#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

OpenGLWidget::~OpenGLWidget()
{
    destroyVBOs();
    destroyShaders();
}

void OpenGLWidget::initializeGL(){
 initializeOpenGLFunctions();
 glClearColor(1,1,1,1); // limpa a janela (coloca uma cor RGBA)
 qDebug("OpenGL Version: %s", glGetString(GL_VERSION));
 qDebug("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

 createShaders();
 createVBOs();
 changeDiagonal();
 // glClearColor(1,0,0,1); // limpa a janela (coloca uma cor RGBA)
 // QObject::connect(&timer, &QTimer::timeout,this,[&](){this->update();});
 // timer.start(10);
}

void OpenGLWidget::resizeGL(int w, int h){
}

void OpenGLWidget::paintGL(){
// blinkFlag = !blinkFlag;
// if (blinkFlag)
//    glClearColor(1,1,1,1);
// else
//    glClearColor(0,0,0,1);
 glClear(GL_COLOR_BUFFER_BIT);
 glUseProgram(shaderProgram);
 glBindVertexArray(vao);
 glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void OpenGLWidget::toggleDarkMode(bool changeToDarkMode){
 makeCurrent();
 if(changeToDarkMode)
     glClearColor(0,0,0,1);
 else
    glClearColor(1,1,1,1);
 update();
}

void OpenGLWidget::createShaders()
{
 makeCurrent();
 destroyShaders();
 QFile vs(":/shaders/vshader1.glsl");
 QFile fs(":/shaders/fshader1.glsl");
 // TODO: Jogar mensagem de erro
 if (!vs.open((QFile::ReadOnly | QFile::Text))) return;
 if (!fs.open((QFile::ReadOnly | QFile::Text))) return;

 auto byteArrayVs{vs.readAll()};
 auto byteArrayFs{fs.readAll()};

 const char *c_strVs{byteArrayVs};
 const char *c_strFs{byteArrayFs};

 vs.close();
 fs.close();

 GLuint vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
 glShaderSource(vertexShader, 1, &c_strVs, 0);
 glCompileShader(vertexShader);

 GLint isCompiled{0};
 glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
 if (isCompiled == GL_FALSE)
 {
    GLint maxLength{0};
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
    qDebug("%s", &infoLog[0]);
    glDeleteShader(vertexShader);
    return;
 }

 GLuint fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
 glShaderSource(fragmentShader, 1, &c_strFs, 0);
 glCompileShader(fragmentShader);

 glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
 if (isCompiled == GL_FALSE)
 {
    GLint maxLength{0};
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
    qDebug("%s", &infoLog[0]);
    glDeleteShader(vertexShader); // necessario apagar o vertex shader mesmo que de erro na compilacao acima
    glDeleteShader(fragmentShader);
    return;
 }

 shaderProgram = glCreateProgram();
 glAttachShader(shaderProgram, vertexShader);
 glAttachShader(shaderProgram, fragmentShader);
 glLinkProgram(shaderProgram);

 GLint isLinked{0};
 glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);

 if (isLinked == GL_FALSE)
 {
    GLint maxLength{0};
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);
    qDebug("%s", &infoLog[0]);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
    return;
 }

 glDetachShader(shaderProgram, vertexShader);
 glDetachShader(shaderProgram, fragmentShader);
 glDeleteShader(vertexShader);
 glDeleteShader(fragmentShader);
}

void OpenGLWidget::destroyShaders()
{
 makeCurrent();
 glDeleteProgram(shaderProgram);
}

void OpenGLWidget::createVBOs()
{
 makeCurrent();
 destroyVBOs();

 vertices.resize(4);
 colors.resize(4);
 indices.resize(6);

 // sem a ultima coordenada o 3D nao renderiza corretamente
 vertices[0] = QVector4D(-0.5,-0.5, 0, 1);
 vertices[1] = QVector4D( 0.5,-0.5, 0, 1);
 vertices[2] = QVector4D( 0.5, 0.5, 0, 1);
 vertices[3] = QVector4D(-0.5, 0.5, 0, 1);

 colors[0] = QVector4D(1,0,0,1);
 colors[1] = QVector4D(0,1,0,1);
 colors[2] = QVector4D(0,0,1,1);
 colors[3] = QVector4D(1,1,0,1);

 indices[0] = 0; indices[1] = 1; indices[2] = 2;
 indices[3] = 2; indices[4] = 3; indices[5] = 0;

 glGenVertexArrays(1, &vao);
 glBindVertexArray(vao);

 glGenBuffers(1,&vboVertices);
 glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
 // static draw: regiao da memoria onde o buffer vai ser alocado
 glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(QVector4D), vertices.data(), GL_STATIC_DRAW);
 glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
 glEnableVertexAttribArray(0);

 glGenBuffers(1,&vboColors);
 glBindBuffer(GL_ARRAY_BUFFER, vboColors);
 glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(QVector4D), colors.data(), GL_STATIC_DRAW);
 glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
 glEnableVertexAttribArray(1);

 glGenBuffers(1, &eboIndices);
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboIndices);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void OpenGLWidget::destroyVBOs()
{
 makeCurrent();
 glDeleteBuffers(1,&vboVertices);
 glDeleteBuffers(1,&vboColors);
 glDeleteBuffers(1,&eboIndices);
 glDeleteVertexArrays(1, &vao);
 vboVertices=0;
 vboColors=0;
 eboIndices=0;
 vao=0;
}

void OpenGLWidget::changeDiagonal()
{
 makeCurrent();
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboIndices);
 auto idx{static_cast<GLuint*>(glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER,0,indices.size()*sizeof(GL_UNSIGNED_INT), GL_MAP_WRITE_BIT))};
 idx[0] = 0; idx[1] = 1; idx[2] = 3;
 idx[3] = 1; idx[4] = 2; idx[5] = 3;
 glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
 update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
 switch(event->key())
 {
 case Qt::Key_Escape:
    changeDiagonal();
//    QApplication::quit();
    break;
 }
}
