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

	auto coordenadas = world_coordenadas;
	world_coordenadas.clear();

	double delta = 0;
	for (unsigned int j = 0; j < coordenadas.size() - 3; j++){
		
		double x1 = coordenadas[j].getX();
		double x2 = coordenadas[j+1].getX();
		double x3 = coordenadas[j+2].getX();
		double x4 = coordenadas[j+3].getX();

		double Cx1 = -(x1/6.0) + (x2/2.0) - (x3/2.0) + (x4/6.0);
		double Cx2 = (x1/2.0) - x2 + (x3/2.0);
		double Cx3 = -(x1/2.0) + (x3/2.0);
		double Cx4 = (x1/6.0) + ((2.0*x2)/3.0) + (x3/6.0);

		delta += tamanhoDosPassos;
		double deltaQuadrado = delta * delta;
		double deltaCubo = deltaQuadrado * delta;

		double fx = Cx4;
		double deltaFx = deltaCubo * Cx1 + deltaQuadrado*Cx2 + delta*Cx3;
		double deltaF2x = 6.0*deltaCubo* Cx1 + 2.0*deltaQuadrado*Cx2;
		double deltaF3x = 6.0*deltaCubo*Cx1;

		double y1 = coordenadas[j].getY();
		double y2 = coordenadas[j+1].getY();
		double y3 = coordenadas[j+2].getY();
		double y4 = coordenadas[j+3].getY();

		double Cy1 = -(y1/6.0) + (y2/2.0) - (y3/2.0) + (y4/6.0);
		double Cy2 = (y1/2.0) - y2 + (y3/2.0);
		double Cy3 = -(y1/2.0) + (y3/2.0);
		double Cy4 = (y1/6.0) + ((2.0*y2)/3.0) + (y3/6.0);

		double fy = Cy4;
		double deltaFy = deltaCubo * Cy1 + deltaQuadrado*Cy2 + delta*Cy3;
		double deltaF2y = 6.0*deltaCubo* Cy1 + 2.0*deltaQuadrado*Cy2;
		double deltaF3y = 6.0*deltaCubo*Cy1;

		int i = 1;
		world_coordenadas.push_back(Coordenadas(fx,fy,0.0,1.0));
		for (; i <= (1.0/delta); i++){
			fx += deltaFx;
			deltaFx += deltaF2x;
			deltaF2x += deltaF3x;

			fy += deltaFy;
			deltaFy += deltaF2y;
			deltaF2y += deltaF3y;

			world_coordenadas.push_back(Coordenadas(fx,fy,0.0,1.0));
		}
	}
}
