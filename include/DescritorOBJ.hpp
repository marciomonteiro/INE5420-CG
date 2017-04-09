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
 *	course lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_DESCRITOROBJ_HPP_
#define INCLUDE_DESCRITOROBJ_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cerrno>
#include "Objeto.hpp"
#include "World.hpp"
#include "formas/Ponto.hpp"
#include "formas/Linha.hpp"
#include "formas/Poligono.hpp"

class DescritorOBJ {
private:
	std::string log;
	World * world;
public:
	DescritorOBJ(World* mundo) : log(""), world(mundo){}
	~DescritorOBJ(){}
	std::string transcrevaObjeto(Objeto* obj, std::string objectPath);
	std::string leiaObjetoFromPath(std::string pathToObject);
	// std::vector<std::string> getObjetosFromPath(std::string pathToObjects);
	// void criaObjetosFromPathRoot();
	std::string criaObjetoEadicionaNoMundo(std::string nome, std::string tipo, std::vector<Coordenadas> coordenadas);
};
#endif /* INCLUDE_DESCRITOROBJ_HPP_ */