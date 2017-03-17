/*
 * World.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */


#include "World.hpp"

bool World::adicionaObjetosNoMundo(Objeto* obj){
	return objetosNoMundo.addObjectInTheWorld(obj);
}

void World::destroiObjetosDoMundo(){
	for (auto obj : objetosNoMundo.getAllObjectsFromTheWorld()){
		objetosNoMundo.removeObjectFromTheWorld((obj.second)->getName());
	}
}

void World::redesenhar(){
	for (auto obj : objetosNoMundo.getAllObjectsFromTheWorld()){
		(obj.second)->desenhar();
	}
}