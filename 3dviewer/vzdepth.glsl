#version 400

layout(location = 0) in vec4 vPosition;

// novos inputs do 3dviewer para o shader
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 v2fcolor;

void main()
{
    gl_Position = model * vPosition;
    float gray = (gl_Position.z + 1) * 0.5;
    v2fcolor = vec4(gray, gray, gray, 1);

    // multiplicação pela view: posiciona os vértices em relação à câmera
    // multiplicação pela projection: projeta os vertices de 3D para 2D de forma parametrizada
    gl_Position = projection * view * gl_Position;
}
