/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Window.hpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	curse lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_WINDOW_HPP_
#define INCLUDE_WINDOW_HPP_

#include <iostream>
#include "DisplayFile.hpp"
#include "Coordenadas.hpp"

class Window {
private:
	Coordenadas *inicioDaWindow, *fimDaWindow;
public:
	Window(Coordenadas* inicio, Coordenadas* fim, DisplayFile * world) : inicioDaWindow(inicio), fimDaWindow(fim), displayFile(world){}
	~Window(){}

	void zoom(double porcentagem);
	void mover(double x, double y, double z);
	void setCoordenadas(Coordenadas* inicio, Coordenadas* fim){inicioDaWindow = inicio; fimDaWindow = fim;}
	Coordenadas* getInicioDaWindow(){return inicioDaWindow;}
	Coordenadas* getFimDaWindow(){return fimDaWindow;}
};
#endif /* INCLUDE_WINDOW_HPP_ */
