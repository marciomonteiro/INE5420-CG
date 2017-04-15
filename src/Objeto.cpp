/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Objeto.cpp
 *
 *  Created on: $13 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	curse lectured in Federal University of Santa Catarina.
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
	for (auto& coord : world_coordenadas){
		std::vector<double> tmp0 = {coord.getX(), coord.getY(), 1};
		Matriz::Matriz<double> tmp = Matriz::Matriz<double>(1u,3u,tmp0);
		Matriz::Matriz<double> tmp2 = tmp * matriz;
		coord.setX(tmp2(0,0));
		coord.setY(tmp2(0,1));
		coord.setZ(0.0);
		coord.setAux(0.0);
	}
}

Coordenadas Objeto::centroDoObjeto(){
	double xDoCentro = 0;
	double yDoCentro = 0;
	for (auto coord : world_coordenadas){
		xDoCentro += coord.getX();
		yDoCentro += coord.getY();
	}
	xDoCentro = xDoCentro/world_coordenadas.size();
	yDoCentro = yDoCentro/world_coordenadas.size();
	return Coordenadas(xDoCentro,yDoCentro, 0.0,0.0);
}
