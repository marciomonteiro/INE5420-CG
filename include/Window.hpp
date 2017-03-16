/*
 * Window.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_WINDOW_HPP_
#define INCLUDE_WINDOW_HPP_

class Window {
public:
	Window(double larguraX, double alturaY) : largura(larguraX), altura(alturaY){}
	~Window(){}

	void zoom(double porcentagem);
	void mover(double x, double y, double z);

	//mexer nas coordenadas zoom
private:
	double altura, largura;
};



#endif /* INCLUDE_WINDOW_HPP_ */
