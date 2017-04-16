/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Linha.hpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_FORMAS_LINHA_HPP_
#define INCLUDE_FORMAS_LINHA_HPP_

#include "../Objeto.hpp"
#include <iostream>

class Linha : public Objeto {
private:
	bool clipaComCS;
public:
	Linha(std::string nomeLinha, std::string tipoLinha, std::vector<Coordenadas> coordenadas) : Objeto(nomeLinha, tipoLinha, coordenadas){
		clipaComCS = true;
	}
	~Linha(){}
	void desenhar(cairo_t* cr, std::vector<Coordenadas> coords);
	void clipa();
	void setAlgoritmoDeClipagem(bool algoritmoClipagem);
};
#endif /* INCLUDE_FORMAS_LINHA_HPP_ */
