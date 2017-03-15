/*
 * Objeto.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#include "../include/Objeto.hpp"

void Objeto::setCoordenadas(double x, double y, double z, double aux){
	Coordenadas::setX(x);
	Coordenadas::setY(y);
	Coordenadas::setZ(z);
	Coordenadas::setAux(aux);
}

void Objeto::setCoordenadas2D(double x, double y){
	Coordenadas::setX(x);
	Coordenadas::setY(y);
	Coordenadas::setZ(0);
	Coordenadas::setAux(0);
}

void Objeto::setCoordenadas3D(double x, double y, double z){
	Coordenadas::setX(x);
	Coordenadas::setY(y);
	Coordenadas::setZ(z);
	Coordenadas::setAux(0);
}

const string& Objeto::getName() const {
	return name;
}

const string& Objeto::getTipo() const {
	return tipo;
}