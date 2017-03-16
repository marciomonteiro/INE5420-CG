/*
 * Window.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_WINDOW_HPP_
#define INCLUDE_WINDOW_HPP_

#include "Coordenadas.hpp"

class Window {
public:
	Window();
	Window(const Coordenadas& inicio, const Coordenadas& fim) : incioDaWindow(inicio), fimDaWindow(fim){}
	~Window(){}

	void zoom(double porcentagem);
	void mover(double x, double y, double z);

	//mexer nas Coordenadas zoom
private:
	Coordenadas incioDaWindow, fimDaWindow;
//	World mundo;
};



#endif /* INCLUDE_WINDOW_HPP_ */
