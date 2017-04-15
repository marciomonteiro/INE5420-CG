/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Ponto.hpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	curse lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_FORMAS_PONTO_HPP_
#define INCLUDE_FORMAS_PONTO_HPP_

#include "Objeto.hpp"
#include <gtk/gtk.h>

class Ponto : public Objeto {
public:
	Ponto(std::string nomePonto, std::string tipoPonto, std::vector<Coordenadas> coordenadas) : Objeto(nomePonto, tipoPonto, coordenadas){}
	~Ponto(){}
	void desenhar(cairo_t* surf, std::vector<Coordenadas> coords);
};
#endif /* INCLUDE_FORMAS_PONTO_HPP_ */
