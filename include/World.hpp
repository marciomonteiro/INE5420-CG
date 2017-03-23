/*
 * World.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_WORLD_HPP_
#define INCLUDE_WORLD_HPP_

#include "DisplayFile.hpp"
#include "Matriz.hpp"

class World {
public:
	World(){}
	~World(){}
	bool adicionaObjetosNoMundo(Objeto* obj);
	void removeObjetosNoMundo(std::string nome);
	void destroiTodosObjetosDoMundo();
	DisplayFile* getDisplayfile(){return &world_displayFile;}
	void transformarObjeto(std::string nome, Matriz::Matriz<double> matriz);
	void scalonarObjeto(std::string nome, Matriz::Matriz<double> matriz);
	void rotacionarObjeto(std::string nome, Matriz::Matriz<double> matriz);

private:
	DisplayFile world_displayFile;
};


#endif /* INCLUDE_WORLD_HPP_ */
