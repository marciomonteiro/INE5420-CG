/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 * 
 * Transformacao3D.cpp
 *
 *  Created on: 19 de abr de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 * 	
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina. 
 */

#ifndef INCLUDE_TRANSFORMACAO3D_CPP_
#define INCLUDE_TRANSFORMACAO3D_CPP_

#include "Matriz.hpp"
#include "Coordenadas.hpp"

namespace Transformacao3D {
	/**
	 * Realiza a translacao de um objeto 3D.
	 */
	Matriz::Matriz<double> translacao(double dx, double dy, double dz);

	/**
	 * Realiza o escalonamento de um objeto 3D.
	 */
	Matriz::Matriz<double> escalonamento(double sx, double sy, double sz);

	/**
	 * Realiza a rotacao de um objeto 3D em torno a um eixo arbitrario.
	 */
	Matriz::Matriz<double> rotacao(double grauX, double grauY, double grauZ, Coordenadas eixoArbitrario);
};



#endif /* INCLUDE_TRANSFORMACAO3D_CPP_ */
