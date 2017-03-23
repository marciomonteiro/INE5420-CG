/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Transformacao2D.hpp
 *
 *  Created on: $20 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	curse lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_TRANSFORMACAO2D_HPP_
#define INCLUDE_TRANSFORMACAO2D_HPP_

#include <iostream>
#include "Coordenadas.hpp"
#include <cmath>
#include <vector>
#include "Matriz.hpp"

class Transformacao2D {
public:
	Transformacao2D(){}
	~Transformacao2D(){};
	Matriz::Matriz<double> translacao(double dx, double dy);
	Matriz::Matriz<double> escalonamento(double sx, double sy);
	Matriz::Matriz<double> rotacao(double graus);
};
#endif /* INCLUDE_TRANSFORMACAO2D_HPP_ */
