/*
*	================================================
*		FEDERAL UNIVERSITY OF SANTA CATARINA
*	================================================
*
*	CurvaBSpline.cpp
*
*	Created on: 9 de abr de 2017.
*		Authors: Marcio Monteiro and Rodrigo Pedro Marques.
*		GitHub: https://github.com/marciomonteiro/INE5420-CG.git
*	Professor: Dr. rer.nat. Aldo von Wangenheim
*
*	This file is part of a project for the INE5420 Computer Graphics
*	course lectured in Federal University of Santa Catarina. 
*/

#include "../include/formas/CurvaBSpline.hpp"

void CurvaBSpline::gerarPontosDaCurva(){
	std::cout<<"CurvaBSpline::gerarPontosDaCurva"<<std::endl;
	auto coordenadas = world_coordenadas;
	world_coordenadas.clear();
	int numeroDePontosDaCurva = coordenadas.size();
	double deltinha = tamanhoDosPassos;
	double deltinha2 = deltinha*deltinha;
	double deltinha3 = deltinha2*deltinha;
	for (int i = 0; i < numeroDePontosDaCurva; i++) {

		double cx[4] = {0,0,0,0};
		cx[0] = (1/6)*(coordenadas[i+3].getX() - coordenadas[i].getX()) + (1/2)*(coordenadas[i+1].getX() - coordenadas[i+2].getX());
		cx[1] = (1/2)*(coordenadas[i+2].getX() + coordenadas[i].getX()) - coordenadas[i+1].getX();
		cx[2] = (1/2)*(coordenadas[i+2].getX() - coordenadas[i].getX());
		cx[3] = (1/6)*(coordenadas[i+2].getX() + coordenadas[i].getX()) + (2/3)*coordenadas[i+1].getX();

		double cy[4] = {0,0,0,0};
		cy[0] = (1/6)*(coordenadas[i+3].getY() - coordenadas[i].getY()) + (1/2)*(coordenadas[i+1].getY() - coordenadas[i+2].getY());
		cy[1] = (1/2)*(coordenadas[i+2].getY() + coordenadas[i].getY()) - coordenadas[i+1].getY();
		cy[2] = (1/2)*(coordenadas[i+2].getY() - coordenadas[i].getY());
		cy[3] = (1/6)*(coordenadas[i+2].getY() + coordenadas[i].getY()) + (2/3)*coordenadas[i+1].getY();

		double matrizDeltinhaX[3] = {0,0,0};
		matrizDeltinhaX[0] = deltinha3*cx[0] + cx[1]* deltinha2 + cx[2]*deltinha;
		matrizDeltinhaX[2] = 6*deltinha3*cx[0];
		matrizDeltinhaX[1] = matrizDeltinhaX[2] + 2 * cx[1]* deltinha2;

		double matrizDeltinhaY[3] = {0,0,0};
		matrizDeltinhaY[0] = deltinha3*cy[0] + cy[1]* deltinha2 + cy[2]*deltinha;
		matrizDeltinhaY[2] = 6*deltinha3*cy[0];
		matrizDeltinhaY[1] = matrizDeltinhaY[2] + 2 * cy[1]* deltinha2;

		double xvelho = cx[3];
		double yvelho = cy[3];

		world_coordenadas.push_back(Coordenadas(xvelho,yvelho,0,1));

		for (double i = 0.0; i <= 1.0; i += tamanhoDosPassos) {
			double x = xvelho;
			double y = yvelho;

			x += matrizDeltinhaX[0];
			matrizDeltinhaX[0] += matrizDeltinhaY[1];
			matrizDeltinhaY[1] += matrizDeltinhaY[2];

			y += matrizDeltinhaY[0];
			matrizDeltinhaY[0] += matrizDeltinhaY[1];
			matrizDeltinhaY[1] += matrizDeltinhaY[2];

			world_coordenadas.push_back(Coordenadas(x,y,0,1));

			xvelho = x;
			yvelho = y;
		}
		std::cout<<"size world: "<<world_coordenadas.size()<<std::endl;
	}
}