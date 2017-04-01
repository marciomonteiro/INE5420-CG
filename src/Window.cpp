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
 *	course lectured in Federal University of Santa Catarina.
 */

#include "Window.hpp"

Window::Window(Coordenadas* inicio, Coordenadas* fim, DisplayFile * world){
	inicioDaWindow = inicio;
	fimDaWindow = fim;
	displayfile = world;
	anguloX = 0.0;
	anguloY = 0.0;
	anguloZ = 0.0;
	centroDaWindow = new Coordenadas((inicioDaWindow->getX() + fimDaWindow->getX())/2, (inicioDaWindow->getY() + fimDaWindow->getY())/2,0.0,0.0);
}

void Window::novoAngulo(double x, double y, double z){
	std::cout<<"Window::novoAngulo x: "<<x<<" y: "<<y<<" z: "<<z<<std::endl;
	anguloX += x;
	anguloY += y;
	anguloZ += z;
	std::cout<<"Window::novoAngulo x: "<<anguloX<<" y: "<<anguloY<<" z: "<<anguloZ<<std::endl;
}

void Window::normalizaCoordenadasDoMundo(){
	std::cout<<"Window::normalizaCoordenadasDoMundo"<<std::endl;
	std::vector<double> tmp0 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
	Matriz::Matriz<double> translada = Matriz::Matriz<double>(3u,3u,tmp0);
	Matriz::Matriz<double> rotaciona = Matriz::Matriz<double>(3u,3u,tmp0);
	Matriz::Matriz<double> escala = Matriz::Matriz<double>(3u,3u,tmp0);
	translada(2,0) = -centroDaWindow->getX();
	translada(2,1) = -centroDaWindow->getY();
	double radianos = (M_PI/180)*-anguloX;
	rotaciona(0,0) = cos(radianos);
	rotaciona(0,1) = -sin(radianos);
	rotaciona(1,0) = sin(radianos);
	rotaciona(1,1) = cos(radianos);
	Matriz::Matriz<double> tmp2 = translada * rotaciona;
	escala(0,0) = 2/(fimDaWindow->getX() - inicioDaWindow->getX());
	escala(1,1) = 2/(fimDaWindow->getY() - inicioDaWindow->getY());
	Matriz::Matriz<double> tmp3 = tmp2 * escala;
	std::cout<<"normaliza objetos "<<displayfile->instancia().isEmpty()<<std::endl;
	for (auto &objetos : displayfile->instancia().getAllObjectsFromTheWorld()){
		(objetos.second)->normalizaCoordenadas(tmp3);
		std::cout<<"dentro do for"<<std::endl;
	}
	this->atualizaCentroDaWindow();
}

void Window::atualizaCentroDaWindow(){
	centroDaWindow->setX((fimDaWindow->getX() + inicioDaWindow->getX())/2);
	centroDaWindow->setY((fimDaWindow->getY() + inicioDaWindow->getY())/2);
}

void Window::zoom(double porcentagem){
	double larguraDaWindow = fimDaWindow->getX() - inicioDaWindow->getX();
	double alturaDaWindow = fimDaWindow->getY() - inicioDaWindow->getY();
	larguraDaWindow = larguraDaWindow * porcentagem;
	alturaDaWindow = alturaDaWindow * porcentagem;
	inicioDaWindow->setX(centroDaWindow->getX() - larguraDaWindow/2);
	inicioDaWindow->setY(centroDaWindow->getY() - alturaDaWindow/2);
	fimDaWindow->setX(centroDaWindow->getX() + larguraDaWindow/2);
	fimDaWindow->setY(centroDaWindow->getY() + alturaDaWindow/2);
}

void Window::mover(double x, double y, double z){
	inicioDaWindow->setX(inicioDaWindow->getX()+x);
	inicioDaWindow->setY(inicioDaWindow->getY()+y);
	fimDaWindow->setX(fimDaWindow->getX()+x);
	fimDaWindow->setY(fimDaWindow->getY()+y);
	this->atualizaCentroDaWindow();
}
