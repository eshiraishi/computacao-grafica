#version 400

layout( location = 0) in vec4 vPosition;
layout( location = 1) in vec4 vColors;

// matriz de transformação que será definida em tempo de execução
uniform mat4 mModel;

out vec4 v2fcolor;

void main(){
    gl_Position = mModel*vPosition;
    v2fcolor = vColors;
}
