/*
 * World.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_WORLD_HPP_
#define INCLUDE_WORLD_HPP_

#include "DisplayFile.hpp"

class World {
public:
	World(){}
	~World(){}
	bool adicionaObjetosNoMundo(Objeto* obj);
	void destroiTodosObjetosDoMundo();
	// void redesenhar();

private:
	DisplayFile world_displayfile;
};


#endif /* INCLUDE_WORLD_HPP_ */
