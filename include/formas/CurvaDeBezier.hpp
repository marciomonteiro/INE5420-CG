/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 * 
 * CurvaDeBezier.hpp
 *
 *  Created on: 9 de abr de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 * 	
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina. 
 */

#ifndef INCLUDE_FORMAS_CURVA_DE_BEZIER_HPP_
#define INCLUDE_FORMAS_CURVA_DE_BEZIER_HPP_

#include "../formas/Curva2D.hpp"
#include <iostream>

class CurvaDeBezier : public Curva2D{
public:
	CurvaDeBezier(std::string nomeCurva, std::string tipoCurva, std::vector<Coordenadas> coordenadas) : Curva2D(nomeCurva, tipoCurva, coordenadas){}
	~CurvaDeBezier(){}
	void gerarPontosDaCurva();
};

#endif /* INCLUDE_FORMAS_CURVA_DE_BEZIER_HPP_ */