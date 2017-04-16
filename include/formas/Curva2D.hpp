/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 * 
 * Curva2D.hpp
 *
 *  Created on: 9 de abr de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 * 	
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina. 
 */

#ifndef INCLUDE_FORMAS_CURVA_CPP_
#define INCLUDE_FORMAS_CURVA_CPP_

#include "../Objeto.hpp"
#include <iostream>

class Curva2D : public Objeto{
protected:
	double tamanhoDosPassos = 0.02;
public:
	Curva2D(std::string nomeCurva, std::string tipoCurva, std::vector<Coordenadas> coordenadas) : Objeto(nomeCurva, tipoCurva, coordenadas){}
	~Curva2D(){}
	void desenhar(cairo_t* cr, std::vector<Coordenadas> coords);
	void clipa();
	void gerarPontosDaCurva();
};

#endif /* INCLUDE_FORMAS_CURVA_CPP_ */