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
 *	course lectured in Federal University of Santa Catarina.
 */

#include "Objeto.hpp"

Objeto::Objeto(std::string nomeObjeto, std::string tipoObjeto, std::vector<Coordenadas> coordenadas){
	nome = nomeObjeto;
	std::transform(nome.begin(), nome.end(), nome.begin(), ::tolower);

	tipo = tipoObjeto;
	std::transform(tipo.begin(), tipo.end(), tipo.begin(), ::tolower);

	world_coordenadas = coordenadas;
	normalized_coordenadas = coordenadas;
}

void Objeto::setName(std::string& name){
	nome = name;
	std::transform(nome.begin(), nome.end(), nome.begin(), ::tolower);
}

void Objeto::setTipo(std::string& type){
	tipo = type;
	std::transform(tipo.begin(), tipo.end(), tipo.begin(), ::tolower);
}

std::string Objeto::getName(){
	return nome;
}

std::string& Objeto::getTipo() {
	return tipo;
}

std::vector<Coordenadas>* Objeto::getWorldCoordenadas(){
	return &world_coordenadas;
}

std::vector<Coordenadas>* Objeto::getNormalizedCoordenadas(){
	return &normalized_coordenadas;
}

void Objeto::transformaObjeto(Matriz::Matriz<double> matriz){
	for (auto& coord : world_coordenadas){
		std::vector<double> tmp0 = {coord.getX(), coord.getY(), coord.getZ(), 0.0};
		Matriz::Matriz<double> tmp = Matriz::Matriz<double>(1u,4u,tmp0);
		Matriz::Matriz<double> tmp2 = tmp * matriz;
		coord.setAll(tmp2(0,0), tmp2(0,1), tmp2(0,2));
	}
}

Coordenadas Objeto::centroDoObjeto(){
	double xDoCentro = 0.0;
	double yDoCentro = 0.0;
	double zDoCentro = 0.0;
	for (auto coord : world_coordenadas){
		xDoCentro += coord.getX();
		yDoCentro += coord.getY();
		zDoCentro += coord.getZ();
	}
	xDoCentro = xDoCentro/world_coordenadas.size();
	yDoCentro = yDoCentro/world_coordenadas.size();
	zDoCentro = zDoCentro/world_coordenadas.size();
	return Coordenadas(xDoCentro,yDoCentro, zDoCentro, 1.0);
}

void Objeto::normalizaCoordenadas(Matriz::Matriz<double> normalizadora){
	normalized_coordenadas.clear();
	normalized_coordenadas = world_coordenadas;
	for (auto &coord : normalized_coordenadas){
		std::vector<double> tmp0 = {coord.getX(), coord.getY(), 1.0 ,0.0};
		Matriz::Matriz<double> tmp = Matriz::Matriz<double>(1u,4u,tmp0);
		Matriz::Matriz<double> tmp2 = tmp * normalizadora;
		coord.setAll(tmp2(0,0), tmp2(0,1), tmp2(0,2));
	}
}
