/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 * 
 * DescritorOBJ.hpp
 *
 *  Created on: 27 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 * 	
 *	This file is part of a project for the INE5420 Computer Graphics
 *	curse lectured in Federal University of Santa Catarina. 
 */

#ifndef INCLUDE_DESCRITOROBJ_HPP_
#define INCLUDE_DESCRITOROBJ_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include "Objeto.hpp"

class DescritorOBJ {
public:

	DescritorOBJ() : extensao(".obj"), pathRoot("../objetos/"){}
	~DescritorOBJ(){}

	bool transcrevaObjeto(Objeto* obj);
	Objeto* leiaObjetoFromPath(std::string pathToObject);
	std::vector<std::string> getObjetosFromPath(std::string pathToObjects);

private:
	std::string extensao;
	std::string pathRoot;
};



#endif /* INCLUDE_DESCRITOROBJ_HPP_ */

/**
 * O código entregue com este trabalho deve ser capaz de ler/escrever um mundo em formato Wavefront .obj file, devendo inluir todas as rotinas para leitura/escrita de arquivos .obj.

Sugestões de Modelagem:

Crie uma classe DescritorOBJ capaz de transcrever um objeto gráfico para o formato .obj, tomando seu nome, seu tipo, seus vértices e suas arestas.
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
