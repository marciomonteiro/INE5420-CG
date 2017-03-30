/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 * 
 * DescritorOBJ.cpp
 *
 *  Created on: 27 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 * 	
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#include "../include/DescritorOBJ.hpp"

bool DescritorOBJ::transcrevaObjeto(Objeto* obj){
	std::string objectPath = pathRoot;		// "../objetos/"
	std::string nomeObj = obj->getName();	// "linha"
	nomeObj.append(extensao);				// "linha.obj"
	objectPath.append(nomeObj);				// "../objetos/linha.obj"
	const char * path = objectPath.c_str(); // converte para char

	if(std::ifstream(path)){
		std::cout << "Arquivo " << nomeObj << " ja existe! " << std::endl;
		return false;
	}

	std::ofstream objeto(objectPath);
	std::cout << "Caminho do novo objeto " << objectPath << std::endl;

	if (objeto.is_open()) {
		objeto << "o ";
		objeto << obj->getName();
		objeto << "\n";
		objeto << "g ";
		objeto << obj->getTipo();
		objeto << "\n\n";
		auto coordenadas = obj->getWorldCoordenadas();

		for(auto& coords : *coordenadas) {
			objeto << "v ";
			objeto << coords.getX();
			objeto << " ";
			objeto << coords.getY();
			objeto << " ";
			objeto << coords.getZ();
			objeto << "\n";
		}

		std::cout << "Objeto criado!" << std::endl;
		objeto.close();
	} else {
		std::cout << "Não foi possível abrir o arquivo " << objectPath << std::endl;
		return false;
	}

	return false;
}
//http://www.cplusplus.com/doc/tutorial/files/

/*
# cube.obj
#

g cube

v  0.0  0.0  0.0
v  0.0  0.0  1.0
v  0.0  1.0  0.0
v  0.0  1.0  1.0
v  1.0  0.0  0.0
v  1.0  0.0  1.0
v  1.0  1.0  0.0
v  1.0  1.0  1.0
 */

/**
 * O código entregue com este trabalho deve ser capaz de ler/escrever um mundo em formato Wavefront .obj file, devendo inluir todas as
 * rotinas para leitura/escrita de arquivos .obj.

Sugestões de Modelagem:

Crie uma classe DescritorOBJ capaz de transcrever um objeto gráfico para o formato .obj, tomando seu nome,
seu tipo, seus vértices e suas arestas.
Chame o descritor para cada objeto de seu mundo.
Assim você só precisa se preocupar com o cabeçalho do .obj. O resto de se resove através de um percurso do display file com seu descritor.
 */


/**
Vertex data:
v	Geometric vertices
vt	Texture vertices
vn	Vertex normals
vp	Parameter space vertices
Free-form curve/surface attributes:
deg	Degree
bmat	Basis matrix
step	Step size
cstype	Curve or surface type

Elements:
p	Point
l	Line
f	Face
curv	Curve
curv2	2D curve
surf	Surface

Free-form curve/surface body statements:
parm	Parameter values
trim	Outer trimming loop
hole	Inner trimming loop
scrv	Special curve
sp	Special point
end	End statement

Connectivity between free-form surfaces:
con	Connect

Grouping:
g	Group name
s	Smoothing group
mg	Merging group
o	Object name

Display/render attributes:
bevel	Bevel interpolation
c_interp	Color interpolation
d_interp	Dissolve interpolation
lod	Level of detail
usemtl	Material name
mtllib	Material library
shadow_obj	Shadow casting
trace_obj	Ray tracing
ctech	Curve approximation technique
stech	Surface approximation technique

 */
