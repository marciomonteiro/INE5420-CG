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
	Window(const Coordenadas& inicio, const Coordenadas& fim) : inicioDaWindow(inicio), fimDaWindow(fim){}
	~Window(){}

//	Window(){
//		inicioDaWindow.setX(0);
//		inicioDaWindow.setY(0);
//		inicioDaWindow.setZ(0);
//		inicioDaWindow.setAux(0);
//		fimDaWindow.setZ(0);
//		fimDaWindow.setX(300);
//		fimDaWindow.setY(300);
//		fimDaWindow.setZ(0);
//	}

	void zoom(double porcentagem);
	void mover(double x, double y, double z);

	//mexer nas Coordenadas zoom
private:
	Coordenadas inicioDaWindow, fimDaWindow;
//	World mundo;
};



#endif /* INCLUDE_WINDOW_HPP_ */
