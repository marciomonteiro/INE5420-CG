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

/**
* Método responsável por escrever o documento .obj de um dado objeto.
* O resultado é um arquivo no estilo wavefront file.
* \param obj é um ponteiro para o objeto que será transcrito.
* \return bool retorna verdadeiro caso consiga criar o arquivo e false caso contrário.
*/
std::string DescritorOBJ::transcrevaObjeto(Objeto* obj, std::string objectPath){
	if(std::ifstream(objectPath.c_str())){
		return "===========\nArquivo \'" + obj->getName() + "\' já existe!\n===========\n";
	}
	std::ofstream objeto(objectPath);
	log+= "Caminho do novo objeto "+ objectPath;
	if (objeto.is_open()) {
		objeto<<"o "<<obj->getName()<<"\n"<<"g "<<obj->getTipo()<<"\n\n";
		auto coordenadas = obj->getWorldCoordenadas();
		for(auto& coords : *coordenadas) {
			objeto<<"v "<<coords.getX()<<" "<< coords.getY()<<" "<<coords.getZ()<<"\n";
		}
		objeto<<"# "<<coordenadas->size()<<" vertices.";
		//Faltou as faces
		objeto.close();
		return "Objeto salvo!";
	}
	return "===========\nNão foi possível abrir o arquivo " + objectPath + "\n===========\n";
}

/**
* Lê um arquivo .obj do caminho passado como parâmetro, e cria um Objeto
* do tipo indicado no arquivo.
* \param pathToObject string que indica o caminho do arquivo .obj;
* \return ponteiro para o objeto criado.
*/
std::string DescritorOBJ::leiaObjetoFromPath(std::string pathToObject){
	std::ifstream objFile(pathToObject);
	if (objFile.is_open()) {
		std::string nomeObjeto;
		std::string tipo;
		std::vector<Coordenadas> coords;
		std::string linha;
		std::vector<std::string> linhasDoArquivo;
		while (std::getline(objFile, linha)) {//Transforma cada linha do arquivo em string e adiciona no vetor
			linhasDoArquivo.push_back(linha);
		}
		log += "Arquivo passado para vetores de string.\n";
		std::string token;
		size_t pos = 0;
		std::string delimiter = " ";
		for (auto linha : linhasDoArquivo) {
			log+= "Linha: " + linha + "\n";
			while ((pos = linha.find(delimiter)) != std::string::npos) {
				token = linha.substr(0, pos);
				if(token == "g"){
					linha.erase(0, pos + delimiter.length()); //Remove g -> Nome do grupo
					token = linha.substr(0, linha.length());
					std::transform(token.begin(), token.end(), token.begin(), ::tolower);
					tipo = token;
				} else {
				if (token == "o") {
					linha.erase(0, pos + delimiter.length());	//Remove o -> nome do objeto
					token = linha.substr(0, linha.length());
					nomeObjeto = token;
				} else {
					if (token == "v") {
						linha.erase(0, pos + delimiter.length());	//Remove v -> vertices
						while ((pos = linha.find(delimiter)) != std::string::npos){
							token = linha.substr(0, linha.find(delimiter));
							double x = atof(token.c_str());
							linha.erase(0, linha.find(delimiter) + delimiter.length());
							token = linha.substr(0, linha.find(delimiter));
							double y = atof(token.c_str());
							linha.erase(0, linha.find(delimiter) + delimiter.length());
							token = linha.substr(0, linha.find(delimiter));
							double z = atof(token.c_str());
							linha.erase(0, linha.find(delimiter) + delimiter.length());
							coords.push_back(Coordenadas(x,y,z,0.0));
							}
						} else {
							linha.erase(0, pos + linha.length());	//deleta linha
							continue;
						}
					}
				}
			}
		}
		criaObjetoEadicionaNoMundo(nomeObjeto, tipo, coords);
		log+= "Objeto \'" + nomeObjeto + "\' lido e criado.\n";
		objFile.close();
	} else {
		log+= "===========\nNao foi possivel criar o objeto.\n===========\n";
	}
	return log;
}

/**
 * Cria um objeto e adiciona ele no mundo.
 * \param nomeObjeto nome do objeto a ser criado.
 * \param tipoObjeto tipo do objeto a ser criado.
 * \param coordenadas vetor de coordenadas do objeto.
 * \return log log da criacao do objeto.
 */
std::string DescritorOBJ::criaObjetoEadicionaNoMundo(std::string nomeObjeto, std::string tipoObjeto, std::vector<Coordenadas> coordenadas){
	if (tipoObjeto == "poligono") {
		Poligono * poli = new Poligono(nomeObjeto, tipoObjeto, coordenadas, false);
		world->adicionaObjetosNoMundo(poli);
	} else {
		if (tipoObjeto == "curva") {
			Curva2D * curva = new Curva2D(nomeObjeto, tipoObjeto, coordenadas);
			world->adicionaObjetosNoMundo(curva);
		} else {
			if (tipoObjeto == "linha") {
				Linha * linha = new Linha(nomeObjeto, tipoObjeto, coordenadas);
				world->adicionaObjetosNoMundo(linha);
			} else {
				if (tipoObjeto == "ponto") {
					Ponto * ponto = new Ponto(nomeObjeto, tipoObjeto, coordenadas);
					world->adicionaObjetosNoMundo(ponto);
				} else {
					log+="===========\nErro ao criar o objeto "+nomeObjeto+". Tipo desconhecido.\n===========\n";
				}
			}
		}
	}
	return log;
}
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
