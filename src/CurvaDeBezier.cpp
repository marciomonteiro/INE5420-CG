/*
*	================================================
*		FEDERAL UNIVERSITY OF SANTA CATARINA
*	================================================
*
*	Curva2.cpp
*
*	Created on: 9 de abr de 2017.
*		Authors: Marcio Monteiro and Rodrigo Pedro Marques.
*		GitHub: https://github.com/marciomonteiro/INE5420-CG.git
*	Professor: Dr. rer.nat. Aldo von Wangenheim
*
*	This file is part of a project for the INE5420 Computer Graphics
*	course lectured in Federal University of Santa Catarina. 
*/

#include "../include/formas/CurvaDeBezier.hpp"

void CurvaDeBezier::gerarPontosDaCurva(){
	auto coordenadas = world_coordenadas;
	world_coordenadas.clear();
	int numeroDePontosDaCurva = ((coordenadas.size()-4)/3) + 1;
	for (int i = 0; i < numeroDePontosDaCurva; i++){
		for (double j = 0; j <= 1; j += tamanhoDosPassos){
			auto p1 = coordenadas[i * 3];
			auto p2 = coordenadas[i * 3 + 1];
			auto p3 = coordenadas[i * 3 + 2];
			auto p4 = coordenadas[i * 3 + 3];
			double x = 0;
			double y = 0;
			double tmp1 = j*j;
			double tmp2 = j * j * j;
			x = (-tmp2 + 3 * tmp1 - 3 * j + 1) * p1.getX() + (3 * tmp2 - 6 * tmp1 + 3 * j) * p2.getX() + (-3 * tmp2 + 3 * tmp1) * p3.getX() + (tmp2) * p4.getX();
			y = (-tmp2 + 3 * tmp1 - 3 * j + 1) * p1.getY() + (3 * tmp2 - 6 * tmp1 + 3 * j) * p2.getY() + (-3 * tmp2 + 3 * tmp1) * p3.getY() + (tmp2) * p4.getY();
			world_coordenadas.push_back(Coordenadas(x,y,0,1));
		}
	}
}