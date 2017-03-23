/*
 * Viewport.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_VIEWPORT_HPP_
#define INCLUDE_VIEWPORT_HPP_

#include <iostream>
#include "DisplayFile.hpp"
#include "Coordenadas.hpp"

class Viewport {
private:
	Coordenadas coordenadas_minimas;	//Xmin, Ymin, Zmin
	Coordenadas coordenadas_maximas;	//Xmax, Ymax, Zmax
	Coordenadas calcCoordTransf(Coordenadas inicioDaWindow, Coordenadas fimDaWindow, Coordenadas coordenadas_objeto);
public:
	Viewport(Coordenadas& inicio, Coordenadas& fim) : coordenadas_minimas(inicio), coordenadas_maximas(fim){}
	~Viewport(){}
	void transformada(cairo_t* cr, Coordenadas inicioDaWindow, Coordenadas fimDaWindow, DisplayFile* displayFile);
};
#endif /* INCLUDE_VIEWPORT_HPP_ */