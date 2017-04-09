## Federal University of Santa Catarina (UFSC)
## Department of Informatics and Statistics
## Computer Science Bachelor
### INE5420 - Computer Graphics
### Professor: Dr. rer. nat. Aldo von Wangenheim

Group Members:

Marcio Monteiro<br/>
Rodrigo Pedro Marques

Semester: 2017/1

Works of computer graphics (CG) using C++ and Glade.

#### Compiling and executing ####

1. Open the terminal in the folder
2. run make
3. run ./bin/exec

**1.1 - Conceitos Básicos de Computação Gráfica**

- Histórico
- Display Files
- Window, Viewport e Transformada de Viewport
- Operações de navegação na Window

**1.2 - Transformações Geométricas em 2D e Coordenadas Homogêneas**

- Translação
- Escalonamento
- Rotação
- Sistemas de Coordenadas Homogêneas

**1.3 - Sistemas de Coordenadas da Window**

- Altere a representação dos objetos do mundo para suportar representação em um dos sistemas de coordenadas vistos em aula: *Sistema de Coordenadas Normalizado (SCN)* ou o *Sistema de Coordenadas do Plano de Projeção (PPC)*. Agora a transformada de viewport é feita com estas coordenadas novas.

- Atualize a translação e o zoom da window tendo em vista o novo sistema de coordenadas. A translação em particular deve levar em conta sempre o "para cima" do ponto de vista do usuário.

- Implemente a rotação implementando o algoritmo para gerar a descrição no sistema de coordenadas escolhido.

- Atualize a interface da aplicação para que o usuário possa rotacionar a window também. Como a rotação é sempre ao redor do centro da window, basta um campo para colocar o ângulo de rotação.

- Este trabalho deve ser capaz de ler/escrever um mundo em formato Wavefront .obj file, devendo incluir todas as rotinas para leitura/escrita de arquivos .obj.

Sugestões de Modelagem:

- Crie uma classe DescritorOBJ capaz de transcrever um objeto gráfico para o formato .obj, tomando seu nome, seu tipo, seus vértices e suas arestas.
- Chame o descritor para cada objeto de seu mundo.
- Assim você só precisa se preocupar com o cabeçalho do .obj. O resto de se resove através de um percurso do display file com seu descritor.

## Under development

**1.4 - Incremente seu SGI para suportar clipping dos objetos do mundo**

Implemente as principais técnicas de clipagem para windows retangulares vistas neste capítulo, usando clipagem de pontos e clipagem por C-S, L-B ou NLN para retas, de forma a integrá-las ao seu sistema gráfico de maneira que a transformada de viewport seja aplicada apenas aos objetos resultantes do clipping.

Para ter certeza de que a clipagem está funcionando e não é o algoritmo de clipagem de pontos embutido no seu objeto de interface que está fazendo com que as linhas que você está desenhando sejam cortadas no lugar certo, faça sua viewport ser menor do que o seu objeto de desenho (canvas, subcanvas ou oura coisqa que você escolheu), de maneira que a viewport inicie em coordenadas do tipo 10,10 e termine antes do fim da área de desenho, cmo mostra a figura abaixo, onde a viewport está limitada pela moldura imediatamente interna à área de desenho. Dessa forma, se o seu algoritmo clipar algo de forma incorreta, deixando de recortar algum elemento, você vai enxergar imediatamente pois verá o objeto sair de dentro deste retângulo. Como forma de debugar seu exercíco este é um subterfúgio excelente e torna desnecessário analisar os dados gerados para uma lista enorme de objetos clipados para testar o sistema.

### Requisitos ###

**Clipagem**:

1. Clipagem de Pontos: 

2. (duas) técnicas distintas de clipagem de Segmentos de Reta, à escolha, passíveis de serem intercambiadas/selecionadas pelo usuário em um checkbox.

3. Clipagem de Polígonos (técnica à escolha)

**Representação**: Altere seu SGI para suportar clipping dos objetos do mundo:

- Faça sua Viewport ser menor do que o objeto de desenho da linguagem de programação, com uma moldura ao seu redor. Isto facilita na visualização do clipping e na detecção de erros.

- Implemente o clipping de pontos, retas e polígonos utilizando um dos 3 algoritmos de clipping de retas vistos em aula.

- Estenda seu SGI para suportar polígonos preenchidos, utilizando as primitivas de preenchimento da sua linguagem de programação. O usuário escolhe se o polígono é em modelo de arame ou preenchido no momento de sua criação.

- Implemente o clipping de polígonos preenchidos com o algoritmo de Weiler-Atherton. Para simplificar, considere apenas polígonos sem furos (mas possivelmente côncavos).

More informations [here](http://www.inf.ufsc.br/~awangenh/grafica)