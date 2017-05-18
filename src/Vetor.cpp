/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * Vetor.hpp
 *
 *  Created on: 8 de mai de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#include "Vetor.hpp"

Coordenadas* Vetor::get_pontoA(){
	return pontoA;
}

Coordenadas* Vetor::get_pontoB(){
	return pontoB;
}

void Vetor::set_pontoA(Coordenadas novoPonto){
	this->pontoA = novoPonto;
}

void Vetor::set_pontoB(Coordenadas novoPonto){
	this->pontoB = novoPonto;
}

