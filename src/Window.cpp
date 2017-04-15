/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Window.cpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	curse lectured in Federal University of Santa Catarina.
 */

#include "Window.hpp"

void Window::zoom(double porcentagem){
	double larguraDaWindow = fimDaWindow->getX() - inicioDaWindow->getX();
	double alturaDaWindow = fimDaWindow->getY() - inicioDaWindow->getY();
	double centroDaWindowX = ((fimDaWindow->getX() + inicioDaWindow->getX())/2);
	double centroDaWindowY = ((fimDaWindow->getY() + inicioDaWindow->getY())/2);
	larguraDaWindow = larguraDaWindow * porcentagem;
	alturaDaWindow = alturaDaWindow * porcentagem;
	inicioDaWindow->setX(centroDaWindowX - larguraDaWindow/2);
	inicioDaWindow->setY(centroDaWindowY - alturaDaWindow/2);
	fimDaWindow->setX(centroDaWindowX + larguraDaWindow/2);
	fimDaWindow->setY(centroDaWindowY + alturaDaWindow/2);
}

void Window::mover(double x, double y, double z){
	inicioDaWindow->setX(inicioDaWindow->getX()+x);
	inicioDaWindow->setY(inicioDaWindow->getY()+y);
	fimDaWindow->setX(fimDaWindow->getX()+x);
	fimDaWindow->setY(fimDaWindow->getY()+y);
}
