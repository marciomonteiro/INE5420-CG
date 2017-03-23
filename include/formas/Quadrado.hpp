/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Quadrado.hpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	curse lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_FORMAS_QUADRADO_HPP_
#define INCLUDE_FORMAS_QUADRADO_HPP_

#include "../Objeto.hpp"
#include "Retangulo.hpp"

class Quadrado : public Retangulo {
public:
	Quadrado(std::string nomeQuadrado, std::string tipoQuadrado, std::vector<Coordenadas> coordenadas) : Retangulo(nomeQuadrado, tipoQuadrado, coordenadas){}
	~Quadrado(){}
	void desenhar(cairo_t* surf, std::vector<Coordenadas> coords);
};
#endif /* INCLUDE_FORMAS_QUADRADO_HPP_ */
