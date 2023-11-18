# Semana 4

## Pipeline gráfico

Como enviar dados para a placa de vídeo via QT:

* Vertex Buffer Objects:
    * Conceito do OpenGL para armazenar coordenadas e cores dos vértices
    * Eficiente depois que enviado para a GPU (precisa ser criado na CPU inicialmente)
        * No QT: QVectorXD (X é um número de até 4 dimensões)
        * Implementa métodos de GA / AL comuns
        * 4D: posição e cores
        * 3D: vetores normais
        * 2D: coordenada de texturas
* Vertex Array Objects
    * Estrutura mais recente que manipula os VBOs (obrigatório agora no QT)
    * Compõe vários VBOs
* Element Array Buffer Object (EBO):
    * Armazena os índices dos triângulos na tela
* Shader (vertex e fragment): apresenta na tela os vértices definidos na GPU
    * Executados na GPU
    * Compilado e linkado em tempo de execução
    * Lido como uma string em tempo de execução
* Regiões da memória onde o OpenGL cria buffers:
    * static draw: para enviar uma vez e acessar muitas
    * dynamic draw: tem atualizações pontuais mas é mais lido que acessado
    * stream draw: muitos envios e poucas leituras
