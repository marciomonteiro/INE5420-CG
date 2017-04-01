/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Viewport.hpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */
#ifndef INCLUDE_VIEWPORT_HPP_
#define INCLUDE_VIEWPORT_HPP_

#include <iostream>
#include "DisplayFile.hpp"
#include "Coordenadas.hpp"

class Viewport {
private:
	Coordenadas coordenadas_minimas;	//Xmin, Ymin, Zmin
	Coordenadas coordenadas_maximas;	//Xmax, Ymax, Zmax
	double tamBorda;
	Coordenadas calcCoordTransf(Coordenadas inicioDaWindow, Coordenadas fimDaWindow, Coordenadas coordenadas_objeto);
public:
	Viewport(Coordenadas& inicio, Coordenadas& fim, double tamB) : coordenadas_minimas(inicio), coordenadas_maximas(fim), tamBorda(tamB) {}
	~Viewport(){}
	void transformada(cairo_t* cr, Coordenadas inicioDaWindow, Coordenadas fimDaWindow, DisplayFile* displayFile);
	void desenhaEnquadramento(cairo_t* cr);
};
#endif /* INCLUDE_VIEWPORT_HPP_ */
