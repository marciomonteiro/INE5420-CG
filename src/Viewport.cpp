/*
 * Viewport.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#include "../include/Viewport.hpp"

// Viewport::Viewport(){
// 	coordenadas_minimas = Coordenadas(0.0,0.0,0.0,0.0);
// 	coordenadas_maximas = Coordenadas(300.0,300.0,0.0,0.0);
// }

void Viewport::transformada(cairo_t* cr, Coordenadas inicioDaWindow, Coordenadas fimDaWindow, DisplayFile* displayFile){
	for (auto obj : displayFile->getAllObjectsFromTheWorld()){
		std::vector<Coordenadas> coordenadasDaViewPort;
		std::vector<Coordenadas>* coordsObjeto = obj.second->getCoordenadas();
		for (auto coordenadas_objeto : *coordsObjeto)
		{
			coordenadas_objeto = calcCoordTransf(inicioDaWindow, fimDaWindow, coordenadas_objeto);
			coordenadasDaViewPort.push_back(coordenadas_objeto);
		}
		(obj.second)->desenhar(cr, coordenadasDaViewPort);
	}
}

Coordenadas Viewport::calcCoordTransf(Coordenadas inicioDaWindow, Coordenadas fimDaWindow, Coordenadas coordenadas_objeto){
	double xViewport = ((coordenadas_objeto.getX() - inicioDaWindow.getX())/(fimDaWindow.getX() - inicioDaWindow.getX()))*(coordenadas_maximas.getX() - coordenadas_minimas.getX());
	double yViewport = (1 - ((coordenadas_objeto.getY() - inicioDaWindow.getY())/(fimDaWindow.getY() - inicioDaWindow.getY())))*(coordenadas_maximas.getY() - coordenadas_minimas.getY());
	return Coordenadas(xViewport, yViewport, 0, 0);
}