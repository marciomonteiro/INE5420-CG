/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Ponto.cpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#include "formas/Ponto.hpp"
#include "Window.hpp"

void Ponto::desenhar(cairo_t* cr, std::vector<Coordenadas> coords){
	cairo_move_to(cr, coords[0].getX(), coords[0].getY());
	cairo_line_to (cr, coords[0].getX() + 1.0, coords[0].getY() + 1.0);
	cairo_close_path(cr);
	cairo_stroke(cr);
}

void Ponto::clipa(){
	Algoritmos::clipaPonto(normalized_coordenadas);
}
