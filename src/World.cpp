/*
 * World.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */


#include "World.hpp"

bool World::adicionaObjetosNoMundo(Objeto* obj){
	return world_displayFile.addObjectInTheWorld(obj);
}

void World::removeObjetosNoMundo(std::string nome){
	world_displayFile.removeObjectFromTheWorld(nome);
}

void World::destroiTodosObjetosDoMundo(){
	for (auto obj : world_displayFile.getAllObjectsFromTheWorld()){
		world_displayFile.removeObjectFromTheWorld((obj.second)->getName());
	}
}