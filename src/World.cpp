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

void World::transformarObjeto(std::string nome, Matriz::Matriz<double> matriz){
	// Objeto* obj = 
	world_displayFile.getTheObjectFromTheWorld(nome)->transformaObjeto(matriz);
	// std::cout<<"mundo transformarObjeto"<<std::endl;
	// // obj->transformaObjeto(matriz);
}
void World::scalonarObjeto(std::string nome, Matriz::Matriz<double> matriz){
	world_displayFile.getTheObjectFromTheWorld(nome)->transformaObjeto(matriz);
}
void World::rotacionarObjeto(std::string nome, Matriz::Matriz<double> matriz){
	// world_displayFile.getTheObjectFromTheWorld(nome)->transformaObjeto(matriz);
}