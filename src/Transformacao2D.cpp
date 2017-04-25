/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Transformacao2D.cpp
 *
 *  Created on: $20 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#include "Transformacao2D.hpp"

Matriz::Matriz<double> Transformacao2D::translacao(double dx, double dy){
	std::vector<double> retorno {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, dx, dy, 1.0};
	return Matriz::Matriz<double>(3u,3u,retorno);
}

Matriz::Matriz<double> Transformacao2D::escalonamento(double sx, double sy){
	std::vector<double> retorno {sx, 0.0, 0.0, 0.0, sy, 0.0, 0.0, 0.0, 1.0};
	return Matriz::Matriz<double>(3u,3u,retorno);
}

Matriz::Matriz<double> Transformacao2D::rotacao(double graus){
	double radianos = (M_PI/180.0)*graus;
	std::vector<double> retorno {cos(radianos), -sin(radianos), 0.0, sin(radianos), cos(radianos), 0.0, 0.0, 0.0, 1.0};
	return Matriz::Matriz<double>(3u,3u,retorno);
}
