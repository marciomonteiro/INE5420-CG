/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Objeto.hpp
 *
 *  Created on: $13 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_OBJETO_HPP_
#define INCLUDE_OBJETO_HPP_

#include <iostream>
#include <gtk/gtk.h>
#include <string>
#include <vector>
#include "Coordenadas.hpp"
#include "Matriz.hpp"

class Objeto{
private:
	std::string nome, tipo;
	std::vector<Coordenadas> world_coordenadas;
	std::vector<Coordenadas> normalized_coordenadas;	//Joel Santana Approves

protected:
	void setName(std::string& name);
	void setTipo(std::string& tipo);
public:
	Objeto(std::string nomeObjeto, std::string tipoObjeto, std::vector<Coordenadas> coordenadas) : nome(nomeObjeto), tipo(tipoObjeto), world_coordenadas(coordenadas), normalized_coordenadas(coordenadas){};
	virtual ~Objeto(){};

	std::string getName();
	std::string& getTipo();
	std::vector<Coordenadas>* getWorldCoordenadas();
	std::vector<Coordenadas>* getNormalizedCoordenadas();

	virtual void desenhar(cairo_t* surf, std::vector<Coordenadas> coords) = 0;	//=0 obriga implementar desenhar
	void transformaObjeto(Matriz::Matriz<double> matriz);
	Coordenadas centroDoObjeto();
};
#endif /* INCLUDE_OBJETO_HPP_ */


