// /*
//  *	================================================
//  *		FEDERAL UNIVERSITY OF SANTA CATARINA
//  *	================================================
//  *
//  * DescritorOBJ.cpp
//  *
//  *  Created on: 27 de mar de 2017.
//  *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
//  *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
//  *	 Professor: Dr. rer.nat. Aldo von Wangenheim
//  *
//  *	This file is part of a project for the INE5420 Computer Graphics
//  *	course lectured in Federal University of Santa Catarina.
//  */
//
// #include "../include/DescritorOBJ.hpp"
//
// /**
//  * Método responsável por escrever o documento .obj de um dado objeto.
//  * O resultado é um arquivo no estilo wavefront file.
//  * \param obj é um ponteiro para o objeto que será transcrito.
//  * \return bool retorna verdadeiro caso consiga criar o arquivo e false caso contrário.
//  */
// bool DescritorOBJ::transcrevaObjeto(Objeto* obj){
// 	std::string objectPath = pathRoot;		// "../objetos/"
// 	std::string nomeObj = obj->getName();	// "linha"
// 	nomeObj.append(extensao);				// "linha.obj"
// 	objectPath.append(nomeObj);				// "../objetos/linha.obj"
// 	const char * path = objectPath.c_str(); // converte para char
//
// 	if(std::ifstream(path)){
// 		std::cout << "Arquivo " << nomeObj << " ja existe! " << std::endl;
// 		return false;
// 	}
//
// 	std::ofstream objeto(objectPath);
// 	std::cout << "Caminho do novo objeto " << objectPath << std::endl;
//
// 	if (objeto.is_open()) {
// 		objeto << "o ";
// 		objeto << obj->getName();
// 		objeto << "\n";
// 		objeto << "g ";
// 		objeto << obj->getTipo();
// 		objeto << "\n\n";
// 		auto coordenadas = obj->getWorldCoordenadas();
//
// 		for(auto& coords : *coordenadas) {
// 			objeto << "v ";
// 			objeto << coords.getX();
// 			objeto << " ";
// 			objeto << coords.getY();
// 			objeto << " ";
// 			objeto << coords.getZ();
// 			objeto << "\n";
// 		}
//
// 		objeto << "# ";
// 		objeto << coordenadas->size();
// 		objeto << " vertices.";
//
// 		//Faltou as faces
//
// 		std::cout << "Objeto criado!" << std::endl;
// 		objeto.close();
// 	} else {
// 		std::cout << "Não foi possível abrir o arquivo " << objectPath << std::endl;
// 		return false;
// 	}
//
// 	return false;
// }
//
// //TODO
// /**
//  * Lê um arquivo .obj do caminho passado como parâmetro, e cria um Objeto
//  * do tipo indicado no arquivo.
//  * \param pathToObject string que indica o caminho do arquivo .obj;
//  * \return ponteiro para o objeto criado.
//  */
// void DescritorOBJ::leiaObjetoFromPath(std::string pathToObject){
// 	std::ifstream objFile(pathToObject);
//
// 	if (objFile.is_open()) {
// 		std::string nomeObjeto;
// 		std::string tipo;
// 		std::vector<Coordenadas> coords;
//
// 		std::string linha;
// 		std::vector<std::string> linhasDoArquivo;
// 		while (std::getline(objFile, linha)) { 		//Transforma cada linha do arquivo em string e adiciona no vetor
// 			linhasDoArquivo.push_back(linha);
// 		}
//
// 		for(auto linha : linhasDoArquivo){
//
// 		}
//
// 		std::cout << "Objeto " << pathToObject << " lido e criado." << std::endl;
// 		objFile.close();
// 	} else {
// 		std::cout << "Nao possivel criar o objeto " << pathToObject << std::endl;
// 	}
// }
//
// /**
//  * Busca os arquivos com extensao definada na classe DescritorOBJ num dado diretório.
//  * \param pathToObjects uma string que indica o caminho a ser procurado.
//  * \return nomeObjetos é um vetor com os nomes dos objetos encontrados no diretório dado.
//  */
// std::vector<std::string> DescritorOBJ::getObjetosFromPath(std::string pathToObjects){
// 	std::vector<std::string> nomeObjetos;
//
// 	DIR* dirFile = opendir( pathToObjects.c_str() );
// 	if(dirFile) {
// 	  struct dirent* hFile;
// 	  errno = 0;
// 	  while (( hFile = readdir( dirFile )) != NULL )
// 	  {
// 		 if (!strcmp( hFile->d_name, ".")) continue;
// 		 if (!strcmp( hFile->d_name, "..")) continue;
// 		 if (strstr( hFile->d_name, extensao.c_str())){
// 			printf( "found file: %s \n", hFile->d_name );
// 			nomeObjetos.push_back(hFile->d_name);
// 		 }
// 	  }
// 	  closedir(dirFile);
// 	}
//
// 	return nomeObjetos;
// }
//
// //TODO
// void DescritorOBJ::criaObjetosFromPathRoot(){
// 	std::vector<std::string> arquivoDosObjetos = getObjetosFromPath(pathRoot);
// 	std::string auxPath = pathRoot;
//
// 	for(auto arquivo : arquivoDosObjetos){
// 		auxPath.append(arquivo);
// 		Objeto* objeto = leiaObjetoFromPath(auxPath);
// 		world->adicionaObjetosNoMundo(objeto);
// 		auxPath = pathRoot;
// 	}
// }
//
//
// /**
// Vertex data:
// v	Geometric vertices
// vt	Texture vertices
// vn	Vertex normals
// vp	Parameter space vertices
// Free-form curve/surface attributes:
// deg	Degree
// bmat	Basis matrix
// step	Step size
// cstype	Curve or surface type
//
// Elements:
// p	Point
// l	Line
// f	Face
// curv	Curve
// curv2	2D curve
// surf	Surface
//
// Free-form curve/surface body statements:
// parm	Parameter values
// trim	Outer trimming loop
// hole	Inner trimming loop
// scrv	Special curve
// sp	Special point
// end	End statement
//
// Connectivity between free-form surfaces:
// con	Connect
//
// Grouping:
// g	Group name
// s	Smoothing group
// mg	Merging group
// o	Object name
//
// Display/render attributes:
// bevel	Bevel interpolation
// c_interp	Color interpolation
// d_interp	Dissolve interpolation
// lod	Level of detail
// usemtl	Material name
// mtllib	Material library
// shadow_obj	Shadow casting
// trace_obj	Ray tracing
// ctech	Curve approximation technique
// stech	Surface approximation technique
//
//  */
