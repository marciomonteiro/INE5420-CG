/*
 * Circulo.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_FORMAS_CIRCULO_HPP_
#define INCLUDE_FORMAS_CIRCULO_HPP_

#include "../Objeto.hpp"

class Circulo {
public:
	Circulo(string nomeCirculo, string tipoObjeto = "Circulo", vector<Coordenadas> coordenadas) : Objeto(nomeCirculo, tipoObjeto, coordenadas){}

	~Circulo(){}

private:
};


#endif /* INCLUDE_FORMAS_CIRCULO_HPP_ */
