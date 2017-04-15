/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $World.hpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_WORLD_HPP_
#define INCLUDE_WORLD_HPP_

#include "DisplayFile.hpp"
#include "Matriz.hpp"

class World {
private:
	DisplayFile world_displayFile;
public:
	World(){};
	~World(){};
	bool adicionaObjetosNoMundo(Objeto* obj);
	void removeObjetosNoMundo(std::string nome);
	void destroiTodosObjetosDoMundo();
	DisplayFile* getDisplayfile();
	void transformarObjeto(std::string nome, Matriz::Matriz<double> matriz);
	void scalonarObjeto(std::string nome, Matriz::Matriz<double> matriz);
	void rotacionarObjeto(std::string nome, bool coordArbitraria, Coordenadas coords, Matriz::Matriz<double> matriz);
};
#endif /* INCLUDE_WORLD_HPP_ */
