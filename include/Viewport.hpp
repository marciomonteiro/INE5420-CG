/*
 * Viewport.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_VIEWPORT_HPP_
#define INCLUDE_VIEWPORT_HPP_

class Viewport {
public:
	Viewport(double larguraX, double alturaY) : largura(larguraX), altura(alturaY){}
	~Viewport(){}

private:
	double altura, largura;
};



#endif /* INCLUDE_VIEWPORT_HPP_ */
