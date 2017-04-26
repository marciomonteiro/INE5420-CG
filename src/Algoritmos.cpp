/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 * 
 * Algoritmos.cpp
 *
 *  Created on: 12 de abr de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 * 	
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina. 
 */

#include "../include/Algoritmos.hpp"

void Algoritmos::setaMetodoClippingReta(bool v){
	clipaMetodo = v;
}

void Algoritmos::clipaPonto(std::vector<Coordenadas>& coord) {
	if (coord.front().getX() < -1.0 || coord.front().getX() > 1.0 ||
		coord.front().getY() < -1.0 || coord.front().getY() > 1.0) {
		coord.clear();
	}
}

void Algoritmos::clipaLinha(std::vector<Coordenadas>& coords) {
	if (clipaMetodo){
		clipaLinhaComCS(coords);
	} else{
		clipaLinhaComLB(coords);
	}
}

void Algoritmos::clipaPoligono(std::vector<Coordenadas>& coords){
	std::vector<Coordenadas> coordsClipadas;
	coords.pop_back();
	Coordenadas ultima = coords.back();
	bool adicionarPonto = false;
	for (unsigned int i = 0; i < coords.size(); i++) {
		std::vector<Coordenadas> linhaAtual = {ultima, coords[i]};
		std::vector<Coordenadas> linhaNoMundo = {ultima, coords[i]};
		Coordenadas pontoMedio = Coordenadas(linhaAtual[0].getX() + linhaAtual[1].getX(), linhaAtual[0].getY() + linhaAtual[1].getY(), 0.0, 1.0);
		clipaLinha(linhaAtual);
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
	coords = coordsClipadas;
}

void Algoritmos::clipaLinhaComCS(std::vector<Coordenadas>& coords){
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
		novoX = coordXaux + (1.0 - coordYaux) / coefAngular;
		novoY = 1.0;
	} else if ((RC01 & 2) != 0) {
		novoX = coordXaux + (-1.0 - coordYaux) / coefAngular;
		novoY = -1.0;
	} else if ((RC01 & 4) != 0) {
		novoX = 1.0;
		novoY = coordYaux + coefAngular * (1.0 - coordXaux);
	} else {
		novoX = -1.0;
		novoY = coordYaux + coefAngular * (-1.0 - coordXaux);
	}
	if (RC01 == RC0) {
		coords[0].setAll(novoX, novoY, 0.0);
	} else {
		coords[1].setAll(novoX, novoY, 0.0);
	}
	clipaLinhaComCS(coords);
}

void Algoritmos::clipaLinhaComLB(std::vector<Coordenadas>& coords){
	double xIni = coords[0].getX();
	double yIni = coords[0].getY();
	double deltaX = coords[1].getX() - xIni;
	double deltaY = coords[1].getY() - yIni;
	std::vector<double> p;
	std::vector<double> q;
	double zta1 = 0.0;
	double zta2 = 1.0;
	double r = 0.0;
	p.push_back(-deltaX);
	p.push_back(deltaX);
	p.push_back(-deltaY);
	p.push_back(deltaY);
	q.push_back(xIni + 1.0);
	q.push_back(1.0 - xIni);
	q.push_back(yIni + 1.0);
	q.push_back(1.0 - yIni);
	for (int i = 0; i < 4; i++) {
		r = q[i]/p[i];
		if (p[i] < 0.0) {
			zta1 = std::max(zta1, r);
		} else {
			zta2 = std::min(zta2, r);
		}
	}
	if (zta1 >= zta2) {
		coords.clear();
		return;
	}
	if (zta1 != 0.0 && zta1 != 1.0) {
		coords[0].setAll(xIni + zta1 * deltaX, yIni + zta1 * deltaY, 0.0);
	}
	if (zta2 != 0.0 && zta2 != 1.0) {
		coords[1].setAll(xIni + zta2 * deltaX, yIni + zta2 * deltaY, 0.0);
	}
}

void Algoritmos::pontoNoCanto(Coordenadas& c){
	if (c.getX() < -1.0)
		c.setX(-1.0);
	if (c.getX() > 1.0)
		c.setX(1.0);
	if (c.getY() < -1.0)
		c.setY(-1.0);
	if (c.getY() > 1.0)
		c.setY(1.0);
}

bool Algoritmos::comparaCoordenadas(Coordenadas coord1, Coordenadas coord2){
	if (coord1.getX() != coord2.getX() || coord1.getY() != coord2.getY()) {
		return false;
	}
	return true;
}

int Algoritmos::determinaRCDeCoordenada(Coordenadas& c){
	int rc = 0;
	rc |= (c.getY() > 1.0);
	rc |= (c.getY() < -1.0) << 1;
	rc |= (c.getX() > 1.0) << 2;
	rc |= (c.getX() < -1.0) << 3;
	return rc;
}

void Algoritmos::clipaCurva(std::vector<Coordenadas>& coords){
	std::vector<Coordenadas> coordTmp;
	for(int i = 0; i < coords.size(); i++){
		std::vector<Coordenadas> linhaAtual = {coords[i], coords[i+1]};
		Algoritmos::clipaLinha(linhaAtual);
		if (coords[i].getX() < -1.0 || coords[i].getX() > 1.0 || coords[i].getY() < -1.0 || coords[i].getY() > 1.0){
			continue;
		}
		Algoritmos::pontoNoCanto(coords[i]);
		coordTmp.push_back(coords[i]);
	}
	coords = coordTmp;
}