/*
 * Window.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_WINDOW_HPP_
#define INCLUDE_WINDOW_HPP_

#include <iostream>
#include "DisplayFile.hpp"
#include "Coordenadas.hpp"

class Window {
public:
	Window();
	Window(const Coordenadas& inicio, const Coordenadas& fim, DisplayFile * world) : inicioDaWindow(inicio), fimDaWindow(fim), displayFile(world){}
	~Window(){}

	void zoom(double porcentagem);
	void mover(double x, double y, double z);

	//mexer nas Coordenadas zoom
private:
	DisplayFile * displayFile;
	Coordenadas inicioDaWindow;
	Coordenadas fimDaWindow;
};



#endif /* INCLUDE_WINDOW_HPP_ */
