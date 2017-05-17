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
Window& Window::instancia() {
    static Window instancia;
    return instancia;
}

Window::Window(){
	inicioDaWindow = new Coordenadas(0.0,0.0,0.0,1.0);
	fimDaWindow = new Coordenadas(400.0,400.0,0.0,1.0);
	anguloX = 0.0;
	anguloY = 0.0;
	anguloZ = 0.0;
	centroDaWindow = new Coordenadas((inicioDaWindow->getX() + fimDaWindow->getX())/2,
									 (inicioDaWindow->getY() + fimDaWindow->getY())/2,
									 0.0,
									 1.0);
	vrp = centroDaWindow;
	Coordenadas *vpn_pontoB = new Coordenadas(0.0, 0.0, 1.0, 0.0);
	vpn = new Vetor(vrp, vpn_pontoB);
}

void Window::setWindow(Coordenadas* inicio, Coordenadas* fim, DisplayFile * world){
	inicioDaWindow->setAll(inicio->getX(),inicio->getY(),inicio->getZ());
	fimDaWindow->setAll(fim->getX(), fim->getY(), fim->getZ());
	displayfile = world;
}

void Window::setCoordsWindow(Coordenadas* inicio, Coordenadas* fim){
	inicioDaWindow->setAll(inicio->getX(),inicio->getY(),inicio->getZ());
	fimDaWindow->setAll(fim->getX(), fim->getY(), fim->getZ());
}

void Window::novoAngulo(double x, double y, double z){
	anguloX += x;
	anguloY += y;
	anguloZ += z;
}

void Window::normalizaCoordenadasDoMundo(){
	Matriz::Matriz<double> translada = Transformacao3D::translacao(-centroDaWindow->getX(), -centroDaWindow->getY(), -centroDaWindow->getZ());
	Matriz::Matriz<double> rotaciona = Transformacao3D::rotacao(anguloX, anguloY, anguloZ);
	Matriz::Matriz<double> escala = Transformacao3D::escalonamento(2/(fimDaWindow->getX() - inicioDaWindow->getX()),
																   2/(fimDaWindow->getY() - inicioDaWindow->getY()),
																   1.0);
	Matriz::Matriz<double> tmp2 = translada * rotaciona;
	Matriz::Matriz<double> tmp3 = tmp2 * escala;
	for (auto &objetos : displayfile->instancia().getAllObjectsFromTheWorld())
		(objetos.second)->normalizaCoordenadas(tmp3);
}

// void Window::normalizaCoordenadasDoMundo(){
// 	Matriz::Matriz<double> translada = Transformacao2D::translacao(-centroDaWindow->getX(), -centroDaWindow->getY());
// 	Matriz::Matriz<double> rotaciona = Transformacao2D::rotacao(anguloX);
// 	Matriz::Matriz<double> escala = Transformacao2D::escalonamento(2/(fimDaWindow->getX() - inicioDaWindow->getX()),2/(fimDaWindow->getY() - inicioDaWindow->getY()));
// 	Matriz::Matriz<double> tmp2 = translada * rotaciona;
// 	Matriz::Matriz<double> tmp3 = tmp2 * escala;
// 	for (auto &objetos : displayfile->instancia().getAllObjectsFromTheWorld())
// 		(objetos.second)->normalizaCoordenadas(tmp3);
// }

void Window::atualizaCentroDaWindow(){
	centroDaWindow->setAll((fimDaWindow->getX() + inicioDaWindow->getX())/2,
						   (fimDaWindow->getY() + inicioDaWindow->getY())/2,
						   0.0);
}

void Window::zoom(double porcentagem){
	double larguraDaWindow = fimDaWindow->getX() - inicioDaWindow->getX();
	double alturaDaWindow = fimDaWindow->getY() - inicioDaWindow->getY();
//	double profDaWindow = fimDaWindow->getZ() - inicioDaWindow->getZ();
	larguraDaWindow = larguraDaWindow * porcentagem;
	alturaDaWindow = alturaDaWindow * porcentagem;
//	profDaWindow = profDaWindow * porcentagem;
//	inicioDaWindow->setAll(centroDaWindow->getX() - larguraDaWindow/2, centroDaWindow->getY() - alturaDaWindow/2, centroDaWindow->getZ() - profDaWindow/2);
	inicioDaWindow->setAll(centroDaWindow->getX() - larguraDaWindow/2, centroDaWindow->getY() - alturaDaWindow/2, 0.0);
//	fimDaWindow->setAll(centroDaWindow->getX() + larguraDaWindow/2, centroDaWindow->getY() + alturaDaWindow/2, centroDaWindow->getZ() - profDaWindow/2);
	fimDaWindow->setAll(centroDaWindow->getX() + larguraDaWindow/2, centroDaWindow->getY() + alturaDaWindow/2, 0.0);
}

void Window::mover(double x, double y, double z){
//	inicioDaWindow->setAll(inicioDaWindow->getX()+x, inicioDaWindow->getY()+y, inicioDaWindow->getZ()+z);
//	fimDaWindow->setAll(fimDaWindow->getX()+x, fimDaWindow->getY()+y, inicioDaWindow->getZ()+z);
	inicioDaWindow->setAll(inicioDaWindow->getX()+x, inicioDaWindow->getY()+y, 0.0);
	fimDaWindow->setAll(fimDaWindow->getX()+x, fimDaWindow->getY()+y, 0.0);
	this->atualizaCentroDaWindow();
}

// void Window::mover(double x, double y, double z){
// 	inicioDaWindow->setAll(inicioDaWindow->getX()+x, inicioDaWindow->getY()+y, 0.0);
// 	fimDaWindow->setAll(fimDaWindow->getX()+x, fimDaWindow->getY()+y, 0.0);
// 	this->atualizaCentroDaWindow();
// }
