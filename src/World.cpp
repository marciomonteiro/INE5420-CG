/*
 * World.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */


#include "World.hpp"

bool World::adicionaObjetosNoMundo(Objeto* obj){
	return world_displayfile.addObjectInTheWorld(obj);
}

void World::destroiTodosObjetosDoMundo(){
	for (auto obj : world_displayfile.getAllObjectsFromTheWorld()){
		world_displayfile.removeObjectFromTheWorld((obj.second)->getName());
	}
}

void World::redesenhar(){
	for (auto obj : world_displayfile.getAllObjectsFromTheWorld()){
		(obj.second)->desenhar();
	}
}