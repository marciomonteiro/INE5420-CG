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
	world_displayFile.getTheObjectFromTheWorld(nome)->transformaObjeto(matriz);
}

void World::scalonarObjeto(std::string nome, Matriz::Matriz<double> matriz){
	world_displayFile.getTheObjectFromTheWorld(nome)->transformaObjeto(matriz);
}

void World::rotacionarObjeto(std::string nome, bool coordAbitraria, Coordenadas coords, Matriz::Matriz<double> matriz){
	std::vector<double> tmp0 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
	Matriz::Matriz<double> tmp1 = Matriz::Matriz<double>(3u,3u,tmp0);
	Matriz::Matriz<double> tmp2 = Matriz::Matriz<double>(3u,3u,tmp0);
	if (coordAbitraria){
		tmp1(2,0) = -coords.getX();
		tmp2(2,0) = coords.getX();
		tmp1(2,1) = -coords.getY();
		tmp2(2,1) = coords.getY();
	} else {
		Coordenadas cd = world_displayFile.getTheObjectFromTheWorld(nome)->centroDoObjeto();
		tmp1(2,0) = -cd.getX();
		tmp2(2,0) = cd.getX();
		tmp1(2,1) = -cd.getY();
		tmp2(2,1) = cd.getY();

	}
	world_displayFile.getTheObjectFromTheWorld(nome)->transformaObjeto(matriz);
}
