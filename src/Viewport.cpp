/*
 * Viewport.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#include "../include/Viewport.hpp"

Viewport::Viewport(){
	std::cout<<"Viewport::Viewport()"<<std::endl;

	coordenadas_minimas.setX(0.0);
	coordenadas_minimas.setY(0.0);
	coordenadas_minimas.setZ(0.0);
	coordenadas_minimas.setAux(0.0);
	coordenadas_maximas.setX(300.0);
	coordenadas_maximas.setY(300.0); 
	coordenadas_maximas.setZ(0.0);
	coordenadas_maximas.setAux(0.0);
}


/**
 * Para cada objeto no mundo, pegar suas coordenadas e aplicar a fórmula.
 */
void Viewport::transformada(Coordenadas inicioDaWindow, Coordenadas fimDaWindow, Coordenadas& coordenadas_objeto){
	std::cout<<"Coordenadas Viewport::transformada(Coordenadas inicioDaWindow, Coordenadas fimDaWindow)"<<std::endl;


// 	for (auto obj : displayfile.getAllObjectsFromTheWorld()){
// 		(obj.second)->desenhar();
	double xViewport = ( coordenadas_objeto.getX() - inicioDaWindow.getX())/(fimDaWindow.getX() - inicioDaWindow.getX())*(coordenadas_minimas.getX() - coordenadas_minimas.getX());
	double yViewport = (1 - ((coordenadas_objeto.getY() - inicioDaWindow.getY())/(fimDaWindow.getY() - inicioDaWindow.getY())))*(coordenadas_minimas.getY() - coordenadas_minimas.getY());
	std::cout<<"xViewport: "<<xViewport<<" yViewport: "<<yViewport<<std::endl;
// 	}
	// for (auto obj : ){
	// 	objetosNoMundo.removeObjectFromTheWorld((obj.second)->getName());
	// }
}
