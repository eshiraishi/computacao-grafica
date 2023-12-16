#version 400

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColors;
// novo input: coordenadas bidimensonais na textura
layout(location = 2) in vec2 vTextCoord;

out vec4 fColors;
// novo output: coordenadas bidimensonais na textura
out vec2 fTextCoord;

void main()
{
    gl_Position = vPosition;
    fColors = vColors;
    // apenas passa os valores para o fragment shader
    fTextCoord = vTextCoord;
}
