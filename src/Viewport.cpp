/*
 * Viewport.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#include "Viewport.hpp"

Viewport::Viewport(){
	std::cout<<"Viewport::Viewport()"<<std::endl;

	inicioDaViewport(0, 0, 0);
	fimDaViewport(300, 300, 0);
}

Coordenadas Viewport::transformada(Coordenadas inicioDaWindow, Coordenadas fimDaWindow){
	std::cout<<"Coordenadas Viewport::transformada(Coordenadas inicioDaWindow, Coordenadas fimDaWindow)"<<std::endl;
	Coordenadas novaCoord;
	double xViewport = ( 100 - inicioDaWindow.getX())/(fimDaWindow.getX() - inicioDaWindow.getX())*(fimDaViewport.getX() - inicioDaViewport.getX());
	double yViewport = (1 - ((100 - inicioDaWindow.getY())/(fimDaWindow.getY() - inicioDaWindow.getY())))*(fimDaViewport.getY() - inicioDaViewport.getY());
	novaCoord.setX(xViewport);
	novaCoord.setY(yViewport);
	novaCoord.setZ(0.0);
	return novaCoord;
}
