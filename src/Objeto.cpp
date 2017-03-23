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
	for (auto& coord : world_coordenadas){
		std::vector<double> tmp0 = {coord.getX(), coord.getY(), 1};
		Matriz::Matriz<double> tmp = Matriz::Matriz<double>(1u,3u,tmp0);
		Matriz::Matriz<double> tmp2 = tmp * matriz;
		// Coordenadas tm(tmp2(0,0),tmp2(0,1),0.0,0.0);
		coord.setX(tmp2(0,0));
		coord.setY(tmp2(0,1));
		coord.setZ(0.0);
		coord.setAux(0.0);
		std::cout<<"X: "<<coord.getX()<<" Y: "<<coord.getY()<<" Z: "<<coord.getZ()<<" Aux: "<<coord.getAux()<<std::endl;
		// for (int i = 0; i < 3; ++i)
		// {
			// std::cout<<"a: "<<tmp0.size()<<std::endl;
		// }
	}
}