/*
 * Retangulo.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_FORMAS_RETANGULO_HPP_
#define INCLUDE_FORMAS_RETANGULO_HPP_

#include "../Objeto.hpp"

class Retangulo {
public:
	Retangulo(string nome, string tipoRetangulo = "Retangulo", vector<Coordenadas> coordenadas) : Objeto(nome, tipoRetangulo, coordenadas){}
	~Retangulo(){}

private:
};


#endif /* INCLUDE_FORMAS_RETANGULO_HPP_ */
