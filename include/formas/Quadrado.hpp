/*
 * Quadrado.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_FORMAS_QUADRADO_HPP_
#define INCLUDE_FORMAS_QUADRADO_HPP_

#include "../Objeto.hpp"

class Quadrado : public Retangulo {
public:
	Quadrado(string nomeQuadrado, string tipoQuadrado = "Quadrado", vector<Coordenadas> coordenadas) : Objeto(nomeQuadrado, tipoQuadrado, coordenadas){}
	~Quadrado(){}

private:
};


#endif /* INCLUDE_FORMAS_QUADRADO_HPP_ */
