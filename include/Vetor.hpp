/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * Vetor.cpp
 *
 *  Created on: 8 de mai de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_VETOR_HPP_
#define INCLUDE_VETOR_HPP_

#include "Coordenadas.hpp"

class Vetor {
private:
	Coordenadas *pontoA, *pontoB;
public:
	/**
	 * Construtor da classe.
	 */
	Vetor(Coordenadas *a, Coordenadas *b) : pontoA(a), pontoB(b){};

	/**
	 * Retorna o ponto A do vetor.
	 * \return ponto A do vetor.
	 */
	Coordenadas* get_pontoA();

	/**
	 * Retorna o ponto B do vetor.
	 * \return ponto B do vetor.
	 */
	Coordenadas* get_pontoB();
};
#endif /* INCLUDE_VETOR_HPP_ */
