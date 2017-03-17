/*
 * Window.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#include "Window.hpp"

Window::Window(){
	std::cout<<"Window::Window()"<<std::endl;
	inicioDaWindow.setX(0.0);
	inicioDaWindow.setY(0.0);
	inicioDaWindow.setZ(0.0);
	inicioDaWindow.setAux(0.0);
	fimDaWindow.setX(300.0);
	fimDaWindow.setY(300.0); 
	fimDaWindow.setZ(0.0);
	fimDaWindow.setAux(0.0);
}

void Window::zoom(double porcentagem){
	std::cout<<"void Window::zoom(double porcentagem)"<<std::endl;
	double larguraDaWindow = fimDaWindow.getX() - inicioDaWindow.getX();
	double alturaDaWindow = fimDaWindow.getY() - inicioDaWindow.getY();

	double centroDaWindowX = (inicioDaWindow.getX() + fimDaWindow.getX())/porcentagem;
	double centroDaWindowY = (inicioDaWindow.getY() + fimDaWindow.getY())/porcentagem;

	std::cout<<"alturaDaWindow: "<<alturaDaWindow<<" larguraDaWindow: "<<larguraDaWindow<<" centroDaWindowX: "<<centroDaWindowX<<" centroDaWindowY: "<<centroDaWindowY<<std::endl;
	
	inicioDaWindow.setX((centroDaWindowX - alturaDaWindow)/porcentagem);
	inicioDaWindow.setY((centroDaWindowY - larguraDaWindow)/porcentagem);

	fimDaWindow.setX((centroDaWindowX + larguraDaWindow)/porcentagem);
	fimDaWindow.setY((centroDaWindowY + alturaDaWindow)/porcentagem);
	std::cout<<"inicioDaWindow.setX(): "<<inicioDaWindow.getX() << " inicioDaWindow.getY(): "<<inicioDaWindow.getY() << " fimDaWindow.getX(): "<<fimDaWindow.getX() << " fimDaWindow.getY(): "<<fimDaWindow.getY() << std::endl;
}

void Window::mover(double x, double y, double z){
	std::cout<<"void Window::mover(double x, double y, double z)"<<std::endl;
	inicioDaWindow.setX(inicioDaWindow.getX()+x);
	inicioDaWindow.setY(inicioDaWindow.getY()+y);

	fimDaWindow.setX(inicioDaWindow.getX()+x);
	fimDaWindow.setY(inicioDaWindow.getY()+y);
	std::cout<<"inicioDaWindow.getX(): "<<inicioDaWindow.getX()<<" inicioDaWindow.getY(): "<<inicioDaWindow.getY()<<" fimDaWindow.getX(): "<<fimDaWindow.getX()<<" fimDaWindow.getY(): "<<fimDaWindow.getY()<<std::endl;
}

