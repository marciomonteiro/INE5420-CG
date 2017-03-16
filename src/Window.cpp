/*
 * Window.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#include "Window.hpp"

Window::Window(){
	incioDaWindow.setX(0);
	incioDaWindow.setY(0);
	fimDaWindow.setZ(0);
	fimDaWindow.setX(300);
	fimDaWindow.setY(300);
	fimDaWindow.setZ(0);
}
//Window::Window(const Coordenadas& inicio, const Coordenadas& fim) : incioDaWindow(inicio), fimDaWindow(fim){}
//Window::~Window(){}

void Window::zoom(double porcentagem){
	double alturaDaWindow = fimDaWindow.getX() - incioDaWindow.getX();
	double larguraDaWindow = fimDaWindow.getY() - incioDaWindow.getY();
	double centroDaWindowX = (incioDaWindow.getX() + fimDaWindow.getX())/2;
	double centroDaWindowY = (incioDaWindow.getY() + fimDaWindow.getY())/2;
	double novaAlturaDaWindow = alturaDaWindow/porcentagem;
	double novaLarguraDaWindow = larguraDaWindow/porcentagem;
	incioDaWindow.setX(centroDaWindowX - novaAlturaDaWindow);
	incioDaWindow.setY(centroDaWindowY - novaLarguraDaWindow);
	fimDaWindow.setX(centroDaWindowX + novaLarguraDaWindow);
	fimDaWindow.setY(centroDaWindowY + novaAlturaDaWindow);
}
void Window::mover(double x, double y, double z){
	incioDaWindow.setX(incioDaWindow.getX()+x);
	incioDaWindow.setY(incioDaWindow.getY()+y);
	fimDaWindow.setX(incioDaWindow.getX()+x);
	fimDaWindow.setY(incioDaWindow.getY()+y);
}

