#version 400

// variavel do outro shader
layout( location = 0) in vec4 vPosition;
layout( location = 1) in vec4 vColors;

out vec4 v2fcolor;
// nesse caso so apresenta o buffer rasteirizado no shader anterior na pipeline

uniform float scaling;
uniform vec4 translation;

void main(){
    gl_Position = (vPosition*vec4(scaling,scaling,scaling,1))+translation;
    v2fcolor = vColors;

}
