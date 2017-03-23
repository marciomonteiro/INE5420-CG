/*
 * Quadrado.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#include "../include/formas/Quadrado.hpp"

void Quadrado::desenhar(cairo_t* cr, std::vector<Coordenadas> coords){
	cairo_set_line_width(cr, 1);
	for (auto coord : coords)
	{
		cairo_move_to(cr, coord.getX(), coord.getY());
		cairo_line_to(cr, coord.getX(), coord.getY());
	}
	cairo_stroke(cr);
}