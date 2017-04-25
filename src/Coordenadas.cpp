/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 * 
 * Coordenadas.cpp
 *
 *  Created on: 29 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 * 	
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina. 
 */

#include "../include/Coordenadas.hpp"

void Coordenadas::setAll(double x, double y, double z){
	this->x=x;
	this->y=y;
	this->z=z;
	this->aux=0.0;
}

void Coordenadas::setX(double x){
	this->x=x;
}

void Coordenadas::setY(double y){
	this->y=y;
}

void Coordenadas::setZ(double z){
	this->z=z;
}

void Coordenadas::setAux(double aux){
	this->aux=aux;
}

double Coordenadas::getX(){
	return x;
}

double Coordenadas::getY(){
	return y;
}

double Coordenadas::getZ(){
	return z;
}

double Coordenadas::getAux(){
	return aux;
}
