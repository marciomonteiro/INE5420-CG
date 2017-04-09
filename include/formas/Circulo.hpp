/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Circulo.hpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_FORMAS_CIRCULO_HPP_
#define INCLUDE_FORMAS_CIRCULO_HPP_

#include "../Objeto.hpp"

class Circulo : public Objeto {
public:
	Circulo(std::string nome, std::string tipo, std::vector<Coordenadas> coordenadas) : Objeto(nome, tipo, coordenadas){}
	~Circulo(){}
	void desenhar(cairo_t* surf, std::vector<Coordenadas> coords);
	void clipa();
};
#endif /* INCLUDE_FORMAS_CIRCULO_HPP_ */
