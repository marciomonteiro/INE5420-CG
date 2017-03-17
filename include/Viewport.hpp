/*
 * Viewport.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_VIEWPORT_HPP_
#define INCLUDE_VIEWPORT_HPP_

#include <iostream>
#include "Coordenadas.hpp"

class Viewport {
public:
	Viewport();
	Viewport(Coordenadas& inicio, Coordenadas& fim) : inicioDaViewport(inicio), fimDaViewport(fim){}
	~Viewport(){}

	Coordenadas transformada(Coordenadas inicioDaWindow, Coordenadas fimDaWindow);
private:
	Coordenadas inicioDaViewport;
	Coordenadas fimDaViewport;
};

#endif /* INCLUDE_VIEWPORT_HPP_ */
