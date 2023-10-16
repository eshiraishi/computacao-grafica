// executado paralelamente para cada vertice
// definido no glEnableVertexAttribArray
// recebe os vetores de posicao e cor
#version 400

in vec4 v2fcolor;

out vec4 outfragcolor;

// avanca a posicao no pipeline do OpenGL via assembly primitivo (deposition)
void main(){
    outfragcolor = v2fcolor;
}
