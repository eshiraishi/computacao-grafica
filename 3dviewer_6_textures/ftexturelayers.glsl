#version 400

in vec3 fN;
in vec3 fV;
in vec3 fL;
in vec2 ftextCoord;

uniform vec4 ambientProduct;
uniform vec4 diffuseProduct;
uniform vec4 specularProduct;
uniform float shininess;


uniform sampler2D layerLower;
uniform sampler2D layerUpper;

out vec4 frag_color;

vec4 Phong(vec3 n)
{
    vec3 N = normalize(n);
    vec3 V = normalize(fV);
    vec3 L = normalize(fL);
    float NdotL = dot(N,L);
    vec3 R = normalize(2.0 *NdotL * N - L);
    float Kd = max(NdotL, 0.0);
    float Ks = (NdotL < 0.0) ? 0.0 : pow(max(dot(R, V), 0.0), shininess);
    // a função mix permite aplicar a composição de duas texturas
    // (que no caso sao usadas a partir dos inputs lower e upper)
    // no caso da nuvem, apenas uma componente da textura é considerada porque está em escala de cinza,
    // deixando a textura sempre branca
    vec4 mixtex = mix(texture(layerLower, ftextCoord), texture(layerUpper, ftextCoord), .4);
    vec4 diffuse = Kd * diffuseProduct * mixtex;
    vec4 specular = Ks * specularProduct;
    vec4 ambient = ambientProduct;
    return ambient + diffuse + specular;
}

void main()
{
    // faz com que a face frontal gerada pelos vértices receba a textura, e o resto seja mixturado com a cor verde
    if (gl_FrontFacing)
    {
        frag_color = vec4(Phong(fN).xyz, 1);
    }
    else
    {
        frag_color = mix(vec4(Phong(-fN).xyz, 1), vec4(0.0, 1.0, 0.0, 1.0), 0.7);
    }
}
