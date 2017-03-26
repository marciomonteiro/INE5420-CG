/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Viewport.cpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	curse lectured in Federal University of Santa Catarina.
 */

#include "../include/Viewport.hpp"

void Viewport::transformada(cairo_t* cr, Coordenadas inicioDaWindow, Coordenadas fimDaWindow, DisplayFile* displayFile){
	for (auto obj : displayFile->getAllObjectsFromTheWorld()){
		std::vector<Coordenadas> coordenadasDaViewPort;
		std::vector<Coordenadas>* coordsObjeto = obj.second->getWorldCoordenadas();
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
