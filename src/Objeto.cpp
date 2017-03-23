/*
 * Objeto.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#include "Objeto.hpp"

std::string Objeto::getName() {
	return nome;
}

const std::string& Objeto::getTipo() const {
	return tipo;
}

void Objeto::setName(std::string& name){
	this->nome = name;
}

void Objeto::setTipo(const std::string& tipo) {
	this->tipo = tipo;
}

void Objeto::transformaObjeto(Matriz::Matriz<double> matriz){
	std::cout<<"objeto transformaObjeto"<<std::endl;
	for (auto coord : world_coordenadas){
		std::vector<double> tmp0 = {coord.getX(), coord.getY(), 1};
		// for (int i = 0; i < 3; ++i)
		// {
			std::cout<<"a: "<<tmp0.size()<<std::endl;
		// }
		Matriz::Matriz<double> tmp = Matriz::Matriz<double>(1u,3u,tmp0);
		Matriz::Matriz<double> tmp2 = tmp * matriz;
	}
}