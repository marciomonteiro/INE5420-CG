# Federal University of Santa Catarina (UFSC)
Department of Informatics and Statistics

Computer Science 

INE5420 - Computer Graphics

Professor: Dr. rer. nat. Aldo von Wangenheim

Group Members:

Marcio Monteiro
Rodrigo Pedro Marques

Semester: 2017/1


Works of computer graphics (CG) using C++.

1.1 - Conceitos Básicos de Computação Gráfica
- Histórico
- Display Files
- Window, Viewport e Transformada de Viewport
- Operações de navegação na Window

1.2 - Transformações Geométricas em 2D e Coordenadas Homogêneas
- Translação
- Escalonamento
- Rotação
- Sistemas de Coordenadas Homogêneas

# Under development

1.3 - Sistemas de Coordenadas da Window:

- Altere a representação dos objetos do mundo para suportar representação em um dos sistemas de coordenadas vistos em aula: *Sistema de Coordenadas Normalizado (SCN)* ou o *Sistema de Coordenadas do Plano de Projeção (PPC)*. Agora a transformada de viewport é feita com estas coordenadas novas.

- Atualize a translação e o zoom da window tendo em vista o novo sistema de coordenadas. A translação em particular deve levar em conta sempre o "para cima" do ponto de vista do usuário.

- Implemente a rotação implementando o algoritmo para gerar a descrição no sistema de coordenadas escolhido.

- Atualize a interface da aplicação para que o usuário possa rotacionar a window também. Como a rotação é sempre ao redor do centro da window, basta um campo para colocar o ângulo de rotação.

- Este trabalho deve ser capaz de ler/escrever um mundo em formato Wavefront .obj file, devendo inluir todas as rotinas para leitura/escrita de arquivos .obj.

Sugestões de Modelagem:

- Crie uma classe DescritorOBJ capaz de transcrever um objeto gráfico para o formato .obj, tomando seu nome, seu tipo, seus vértices e suas arestas.
- Chame o descritor para cada objeto de seu mundo.
- Assim você só precisa se preocupar com o cabeçalho do .obj. O resto de se resove através de um percurso do display file com seu descritor.

For more informations visit: http://www.inf.ufsc.br/~awangenh/grafica