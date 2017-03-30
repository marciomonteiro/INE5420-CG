/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Poligono.hpp
 *
 *  Created on: $13 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_POLIGONO_HPP_
#define INCLUDE_POLIGONO_HPP_

#include "../Objeto.hpp"
#include <iostream>

class Poligono : public Objeto {
private:
	std::vector<Coordenadas> coordenadas; //vertices
public:
	Poligono(std::string nomePoligono, std::string tipoPoligono, std::vector<Coordenadas> coordenadas) : Objeto(nomePoligono, tipoPoligono, coordenadas){}
	~Poligono(){}
	void desenhar(cairo_t* surf, std::vector<Coordenadas> coords);
};
#endif /* INCLUDE_POLIGONO_HPP_ */
