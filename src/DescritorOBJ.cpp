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
bool DescritorOBJ::transcrevaObjeto(Objeto* obj){
	std::string objectPath = pathRoot;// "../objetos/"
	std::string nomeObj = obj->getName();// "linha"
	nomeObj.append(extensao);// "linha.obj"
	objectPath.append(nomeObj);// "../objetos/linha.obj"
	const char * path = objectPath.c_str(); // converte para char

	if(std::ifstream(path)){
		std::cout<<"Arquivo "<<nomeObj<<" ja existe! "<<std::endl;
		return false;
	}
	std::ofstream objeto(objectPath);
	std::cout<<"Caminho do novo objeto "<<objectPath<<std::endl;
	if (objeto.is_open()) {
		objeto<<"o "<<obj->getName()<<"\n"<<"g "<<obj->getTipo()<<"\n\n";
		auto coordenadas = obj->getWorldCoordenadas();
		for(auto& coords : *coordenadas) {
		objeto<<"v "<<coords.getX()<<" "<< coords.getY()<<" "<<coords.getZ()<<"\n";
		}
		objeto<<"# "<<coordenadas->size()<<" vertices.";
		//Faltou as faces
		std::cout<<"Objeto criado!"<<std::endl;
		objeto.close();
	} else {
		std::cout<<"Não foi possível abrir o arquivo "<<objectPath<<std::endl;
		return false;
	}
	return false;
}

/**
* Lê um arquivo .obj do caminho passado como parâmetro, e cria um Objeto
* do tipo indicado no arquivo.
* \param pathToObject string que indica o caminho do arquivo .obj;
* \return ponteiro para o objeto criado.
*/
void DescritorOBJ::leiaObjetoFromPath(std::string pathToObject){
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
		std::cout<<"Arquivo passado para vetores de string. "<<std::endl;
		std::string token;
		size_t pos = 0;
		std::string delimiter = " ";
		for (auto linha : linhasDoArquivo) {
			std::cout<<"Linha: "<<linha<<std::endl;
			while ((pos = linha.find(delimiter)) != std::string::npos) {
				token = linha.substr(0, pos);
				if(token == "g"){
					linha.erase(0, pos + delimiter.length()); //Remove g
					token = linha.substr(0, linha.length());
					std::transform(token.begin(), token.end(), token.begin(), ::tolower);
					tipo = token;
				} else {
				if (token == "o") {
					linha.erase(0, pos + delimiter.length());	//Remove o
					token = linha.substr(0, linha.length());
					nomeObjeto = token;
				} else {
					if (token == "v") {
						linha.erase(0, pos + delimiter.length());	//Remove v
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
		std::cout<<"Objeto "<<pathToObject<<" lido e criado."<<std::endl;
		objFile.close();
	} else {
		std::cout<<"Nao possivel criar o objeto "<<pathToObject<<std::endl;
	}
}

/**
* Busca os arquivos com extensao definada na classe DescritorOBJ num dado diretório.
* \param pathToObjects uma string que indica o caminho a ser procurado.
* \return nomeObjetos é um vetor com os nomes dos objetos encontrados no diretório dado.
*/
std::vector<std::string> DescritorOBJ::getObjetosFromPath(std::string pathToObjects){
	std::vector<std::string> nomeObjetos;
	DIR* dirFile = opendir( pathToObjects.c_str() );
	if(dirFile) {
		struct dirent* hFile;
		errno = 0;
		while (( hFile = readdir( dirFile )) != NULL ){
			if (!strcmp( hFile->d_name, ".")) continue;
			if (!strcmp( hFile->d_name, "..")) continue;
			if (strstr( hFile->d_name, extensao.c_str())){
				std::cout<<"found file: "<< hFile->d_name <<std::endl;
				nomeObjetos.push_back(hFile->d_name);
			}
		}
		closedir(dirFile);
	}
	return nomeObjetos;
}

/**
* Método para criar todos os .obj inclusos na pasta "./objetos/" do projeto.
*/
void DescritorOBJ::criaObjetosFromPathRoot(){
	std::vector<std::string> arquivoDosObjetos = getObjetosFromPath(pathRoot);
	std::string auxPath = pathRoot;
	for(auto arquivo : arquivoDosObjetos){
		auxPath.append(arquivo);
		std::cout<<"Lendo arquivo "<<arquivo<<" do caminho "<<auxPath<<std::endl;
		leiaObjetoFromPath(auxPath);
		auxPath = pathRoot;
	}
	std::cout<<"Criacao dos .obj finalizada."<<std::endl;
}

void DescritorOBJ::criaObjetoEadicionaNoMundo(std::string nomeObjeto, std::string tipoObjeto, std::vector<Coordenadas> coordenadas){
	if (tipoObjeto == "poligono") {
		Poligono * poli = new Poligono(nomeObjeto, tipoObjeto, coordenadas);
		world->adicionaObjetosNoMundo(poli);
	} else {
	if (tipoObjeto == "linha") {
		Linha * linha = new Linha(nomeObjeto, tipoObjeto, coordenadas);
		world->adicionaObjetosNoMundo(linha);
		} else {
		if (tipoObjeto == "ponto") {
			Ponto * ponto = new Ponto(nomeObjeto, tipoObjeto, coordenadas);
			world->adicionaObjetosNoMundo(ponto);
		} else {
			std::cout<<"Erro ao criar objeto. Tipo desconhecido"<<std::endl;
		}
}
	}
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
