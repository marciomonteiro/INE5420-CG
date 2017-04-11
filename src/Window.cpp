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
	inicioDaWindow = new Coordenadas(0,0,0,1);
	fimDaWindow = new Coordenadas(410,400,0,1);
	anguloX = 0.0;
	anguloY = 0.0;
	anguloZ = 0.0;
	centroDaWindow = new Coordenadas((inicioDaWindow->getX() + fimDaWindow->getX())/2, (inicioDaWindow->getY() + fimDaWindow->getY())/2,0,1);
}

void Window::setWindow(Coordenadas* inicio, Coordenadas* fim, DisplayFile * world){
	inicioDaWindow->setAll(inicio->getX(),inicio->getY(),0);
	fimDaWindow->setAll(fim->getX(), fim->getY(), 0);
	displayfile = world;
}

void Window::setCoordsWindow(Coordenadas* inicio, Coordenadas* fim){
	inicioDaWindow->setAll(inicio->getX(),inicio->getY(),0);
	fimDaWindow->setAll(fim->getX(), fim->getY(), 0);
}

void Window::novoAngulo(double x, double y, double z){
	anguloX += x;
	anguloY += y;
	anguloZ += z;
}
void Window::normalizaCoordenadasDoMundo(){
	Matriz::Matriz<double> translada = Transformacao2D::translacao(-centroDaWindow->getX(), -centroDaWindow->getY());
	Matriz::Matriz<double> rotaciona = Transformacao2D::rotacao(anguloX);
	Matriz::Matriz<double> escala = Transformacao2D::escalonamento(2/(fimDaWindow->getX() - inicioDaWindow->getX()),2/(fimDaWindow->getY() - inicioDaWindow->getY()));
	Matriz::Matriz<double> tmp2 = translada * rotaciona;
	Matriz::Matriz<double> tmp3 = tmp2 * escala;
	for (auto &objetos : displayfile->instancia().getAllObjectsFromTheWorld())
		(objetos.second)->normalizaCoordenadas(tmp3);
	// this->atualizaCentroDaWindow();
}

void Window::atualizaCentroDaWindow(){
	centroDaWindow->setAll((fimDaWindow->getX() + inicioDaWindow->getX())/2, (fimDaWindow->getY() + inicioDaWindow->getY())/2, 0);
}

void Window::zoom(double porcentagem){
	double larguraDaWindow = fimDaWindow->getX() - inicioDaWindow->getX();
	double alturaDaWindow = fimDaWindow->getY() - inicioDaWindow->getY();
	larguraDaWindow = larguraDaWindow * porcentagem;
	alturaDaWindow = alturaDaWindow * porcentagem;
	inicioDaWindow->setAll(centroDaWindow->getX() - larguraDaWindow/2, centroDaWindow->getY() - alturaDaWindow/2, 0);
	fimDaWindow->setAll(centroDaWindow->getX() + larguraDaWindow/2, centroDaWindow->getY() + alturaDaWindow/2, 0);
}

void Window::mover(double x, double y, double z){
	inicioDaWindow->setAll(inicioDaWindow->getX()+x, inicioDaWindow->getY()+y, 0);
	fimDaWindow->setAll(fimDaWindow->getX()+x, fimDaWindow->getY()+y, 0);
	this->atualizaCentroDaWindow();
}

void Window::clipaPonto(std::vector<Coordenadas>& coord) {
	if (coord.front().getX() < -1 || coord.front().getX() > 1 ||
		coord.front().getY() < -1 || coord.front().getY() > 1) {
		coord.clear();
	}
}

void Window::setaAlgoritmoClippingReta(bool b){
	clipaComCS = b;
}

void Window::clipaLinha(std::vector<Coordenadas>& coords) {
	std::cout<<"Window::clipaLinha"<<std::endl;
	for (auto coord : coords) {
		std::cout<<"cooords:\n X: "<<coord.getX()<<" Y "<<coord.getY()<<std::endl;
	}
	if (clipaComCS){
		clipaLinhaComCS(coords);
		return;
	}
	clipaLinhaComLB(coords);
}

int Window::determinaRCDeCoordenada(Coordenadas& c) {
	int rc = 0;
	rc |= (c.getY() > 1);
	rc |= (c.getY() < -1) << 1;
	rc |= (c.getX() > 1) << 2;
	rc |= (c.getX() < -1) << 3;
	return rc;
}

void Window::clipaLinhaComCS(std::vector<Coordenadas>& coords){
	auto RC0 = determinaRCDeCoordenada(coords[0]);
	auto RC1 = determinaRCDeCoordenada(coords[1]);
	if (RC0 == 0 && RC1 == 0) {
		return;
	}
	if ((RC0 & RC1) != 0) {
		coords.clear();
		return;
	}
	int RC01 = (RC0 == 0) ? RC1 : RC0;
	double coordXaux = coords[0].getX();
	double coordYaux = coords[0].getY();
	double coefAngular = (coords[1].getY() - coordYaux) / (coords[1].getX() - coordXaux);
	double novoX, novoY;
	if ((RC01 & 1) != 0) {
		novoX = coordXaux + (1 - coordYaux) / coefAngular;
		novoY = 1;
	} else if ((RC01 & 2) != 0) {
		novoX = coordXaux + (-1 - coordYaux) / coefAngular;
		novoY = -1;
	} else if ((RC01 & 4) != 0) {
		novoX = 1;
		novoY = coordYaux + coefAngular * (1 - coordXaux);
	} else {
		novoX = -1;
		novoY = coordYaux + coefAngular * (-1 - coordXaux);
	}
	if (RC01 == RC0) {
		coords[0].setAll(novoX, novoY, 0);
	} else {
		coords[1].setAll(novoX, novoY, 0);
	}
	clipaLinhaComCS(coords);
}

void Window::clipaLinhaComLB(std::vector<Coordenadas>& coords){
	double xIni = coords[0].getX();
	double yIni = coords[0].getY();
	double deltaX = coords[1].getX() - xIni;
	double deltaY = coords[1].getY() - yIni;
	std::vector<double> p;
	std::vector<double> q;
	double zta1 = 0;
	double zta2 = 1;
	double r = 0;
	p.push_back(-deltaX);
	p.push_back(deltaX);
	p.push_back(-deltaY);
	p.push_back(deltaY);
	q.push_back(xIni + 1);
	q.push_back(1 - xIni);
	q.push_back(yIni + 1);
	q.push_back(1 - yIni);
	for (int i = 0; i < 4; i++) {
		r = q[i]/p[i];
		if (p[i] < 0) {
			zta1 = std::max(zta1, r);
		} else {
			zta2 = std::min(zta2, r);
		}
	}
	if (zta1 >= zta2) {
		coords.clear();
		return;
	}
	if (zta1 != 0 && zta1 != 1) {
		coords[0].setAll(xIni + zta1 * deltaX, yIni + zta1 * deltaY, 0);
	}
	if (zta2 != 0 && zta2 != 1) {
		coords[1].setAll(xIni + zta2 * deltaX, yIni + zta2 * deltaY, 0);
	}
}
void pontoNoCanto(Coordenadas& c) {
	if (c.getX() < -1)
		c.setX(-1);
	if (c.getX() > 1)
		c.setX(1);
	if (c.getY() < -1)
		c.setY(-1);
	if (c.getY() > 1)
		c.setY(1);
}

bool comparaCoordenadas(Coordenadas coord1, Coordenadas coord2){
	if (coord1.getX() != coord2.getX() || coord1.getY() != coord2.getY()) {
		return false;
	}
	return true;
}

void Window::clipaPoligono(std::vector<Coordenadas>& coords){
	std::vector<Coordenadas> coordsClipadas;
	coords.pop_back();
	Coordenadas ultima = coords.back();
	bool adicionarPonto = false;
	for (unsigned int i = 0; i < coords.size(); i++) {
		std::vector<Coordenadas> linhaAtual = {ultima, coords[i]};
		std::vector<Coordenadas> linhaNoMundo = {ultima, coords[i]};
		Coordenadas pontoMedio = Coordenadas(linhaAtual[0].getX() + linhaAtual[1].getX(), linhaAtual[0].getY() + linhaAtual[1].getY(), 0, 1);
		std::cout<<"ponto medio:\n X: "<<pontoMedio.getX()<<" Y "<<pontoMedio.getY()<<std::endl;
		std::cout<<"linhaAtual:\n Xi: "<<linhaAtual[0].getX()<<" Yi "<<linhaAtual[0].getY()<<" Xf: "<<linhaAtual[1].getX()<<" Yf "<<linhaAtual[1].getY()<<std::endl;
		clipaLinha(linhaAtual);
		std::cout<<"clipou linhaAtual:\n Xi: "<<linhaAtual[0].getX()<<" Yi "<<linhaAtual[0].getY()<<" Xf: "<<linhaAtual[1].getX()<<" Yf "<<linhaAtual[1].getY()<<std::endl;
		bool linhaFoiClipada = false;
		if (comparaCoordenadas(linhaAtual[0], linhaNoMundo[0]) || comparaCoordenadas(linhaAtual[1], linhaNoMundo[1]))
			linhaFoiClipada = true;
		if (linhaAtual.size() > 1) {
			if (linhaFoiClipada || !adicionarPonto || coordsClipadas.empty() || comparaCoordenadas(linhaAtual[0], coordsClipadas.back())) {
				coordsClipadas.push_back(linhaAtual[0]);
				linhaFoiClipada = false;
			}
			coordsClipadas.push_back(linhaAtual[1]);
			pontoNoCanto(linhaNoMundo[1]);
			coordsClipadas.push_back(linhaNoMundo[1]);
			adicionarPonto = true;
		} else {
			Coordenadas clipaPonto(coords[i]);
			pontoNoCanto(coords[i]);
			pontoNoCanto(pontoMedio);
			coordsClipadas.push_back(coords[i]);
			coordsClipadas.push_back(pontoMedio);
			adicionarPonto = false;
		}
		ultima = coords[i];
	}
	// coords.clear();
	std::cout<<"Window::clipaPoligono\ncoordsClipadas.size: "<<coordsClipadas.size()<<" coords.size: "<<coords.size()<<std::endl;
	for (auto coord : coordsClipadas) {
		std::cout<<"cooords:\n X: "<<coord.getX()<<" Y "<<coord.getY()<<std::endl;
	}
	coords = coordsClipadas;
}
	