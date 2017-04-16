/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 * 
 * Curva2D.cpp
 *
 *  Created on: 9 de abr de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 * 	
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina. 
 */

#include "../include/formas/Curva2D.hpp"

void Curva2D::desenhar(cairo_t* cr, std::vector<Coordenadas> coords){
	cairo_set_line_width(cr, 1);
	cairo_move_to(cr, coords[0].getX(), coords[0].getY());
	for (auto coord : coords)
		cairo_line_to(cr, coord.getX(), coord.getY());
	cairo_stroke(cr);
}

void Curva2D::clipa(){
	Algoritmos::clipaCurva(normalized_coordenadas);
}

void Curva2D::gerarPontosDaCurva(){
}
