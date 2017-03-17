/*
 * Viewport.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#include "../include/Viewport.hpp"

Viewport::Viewport(){
	std::cout<<"Viewport::Viewport()"<<std::endl;

	coordenadas_minimas(0, 0, 0);
	coordenadas_maximas(300, 300, 0);
}

void Viewport::transformada(Coordenadas inicioDaWindow, Coordenadas fimDaWindow, Coordenadas& coordenadas_objeto){
	std::cout<<"Coordenadas Viewport::transformada(Coordenadas inicioDaWindow, Coordenadas fimDaWindow)"<<std::endl;


	for (auto obj : ){
		objetosNoMundo.removeObjectFromTheWorld((obj.second)->getName());
	}
	double xViewport = ( coordenadas_objeto.getX() - inicioDaWindow.getX())/(fimDaWindow.getX() - inicioDaWindow.getX())*(coordenadas_minimas.getX() - coordenadas_minimas.getX());
	double yViewport = (1 - ((coordenadas_objeto.getY() - inicioDaWindow.getY())/(fimDaWindow.getY() - inicioDaWindow.getY())))*(coordenadas_minimas.getY() - coordenadas_minimas.getY());



}
