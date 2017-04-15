/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Retangulo.hpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	curse lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_FORMAS_RETANGULO_HPP_
#define INCLUDE_FORMAS_RETANGULO_HPP_

#include "../Objeto.hpp"

class Retangulo : public Objeto{
public:
	Retangulo(std::string nomeRetangulo, std::string tipoRetangulo, std::vector<Coordenadas> coordenadas) : Objeto(nomeRetangulo, tipoRetangulo, coordenadas){}
	~Retangulo(){}
	void desenhar(cairo_t* surf, std::vector<Coordenadas> coords);
};
#endif /* INCLUDE_FORMAS_RETANGULO_HPP_ */
