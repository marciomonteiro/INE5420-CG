/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Poligono.cpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */
#include "../include/formas/Poligono.hpp"
#include "Window.hpp"

void Poligono::desenhar(cairo_t* cr, std::vector<Coordenadas> coords){
	cairo_set_line_width(cr, 1);
	cairo_move_to(cr, coords.at(0).getX(), coords.at(0).getY());
	for (auto coord : coords)
		cairo_line_to(cr, coord.getX(), coord.getY());
	if (preenchido) {
		cairo_fill(cr);
	} else {
		cairo_close_path(cr);
	}
	cairo_stroke(cr);
}

void Poligono::clipa(){
	Window::instancia().clipaPoligono(normalized_coordenadas);
}

void Poligono::setPreenchimento(bool estado){
	this->preenchido = estado;
}
