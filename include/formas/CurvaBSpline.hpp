/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 * 
 * CurvaBSpline.hpp
 *
 *  Created on: 9 de abr de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 * 	
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina. 
 */

#ifndef INCLUDE_FORMAS_CURVA_B_SPLINE_HPP_
#define INCLUDE_FORMAS_CURVA_B_SPLINE_HPP_

#include "../formas/Curva2D.hpp"
#include <iostream>

class CurvaBSpline : public Curva2D{
public:
	CurvaBSpline(std::string nomeCurva, std::string tipoCurva, std::vector<Coordenadas> coordenadas) : Curva2D(nomeCurva, tipoCurva, coordenadas){}
	~CurvaBSpline(){}
	void gerarPontosDaCurva();
};

#endif /* INCLUDE_FORMAS_CURVA_B_SPLINE_HPP_ */