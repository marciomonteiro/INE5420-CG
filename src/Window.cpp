/*
 * Window.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#include "../include/Window.hpp"

void Window::zoom(double porcentagem){
	double alturaDaWindow = fimDaWindow.getX() - inicioDaWindow.getX();
	double larguraDaWindow = fimDaWindow.getY() - inicioDaWindow.getY();
	double centroDaWindowX = (inicioDaWindow.getX() + fimDaWindow.getX())/2;
	double centroDaWindowY = (inicioDaWindow.getY() + fimDaWindow.getY())/2;
	double novaAlturaDaWindow = alturaDaWindow/porcentagem;
	double novaLarguraDaWindow = larguraDaWindow/porcentagem;
	inicioDaWindow.setX(centroDaWindowX - novaAlturaDaWindow);
	inicioDaWindow.setY(centroDaWindowY - novaLarguraDaWindow);
	fimDaWindow.setX(centroDaWindowX + novaLarguraDaWindow);
	fimDaWindow.setY(centroDaWindowY + novaAlturaDaWindow);
}
void Window::mover(double x, double y, double z){
	inicioDaWindow.setX(inicioDaWindow.getX()+x);
	inicioDaWindow.setY(inicioDaWindow.getY()+y);
	fimDaWindow.setX(inicioDaWindow.getX()+x);
	fimDaWindow.setY(inicioDaWindow.getY()+y);
}

