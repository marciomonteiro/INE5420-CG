/*
 * Viewport.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_VIEWPORT_HPP_
#define INCLUDE_VIEWPORT_HPP_
#include "Coordenadas.hpp"
class Viewport {
public:
	Viewport(Coordenadas& larguraX, Coordenadas& alturaY) : larguraDaViewport(larguraX), alturaDaViewport(alturaY){}
	~Viewport(){}

	void transformada();
private:
	Coordenadas larguraDaViewport;
	Coordenadas alturaDaViewport;
	//double altura, largura;
};



#endif /* INCLUDE_VIEWPORT_HPP_ */
