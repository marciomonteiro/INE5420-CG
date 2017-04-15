/*
 * Quadrado.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_FORMAS_QUADRADO_HPP_
#define INCLUDE_FORMAS_QUADRADO_HPP_

#include "../Objeto.hpp"
#include "Retangulo.hpp"

class Quadrado : public Retangulo {
public:
	Quadrado(std::string nomeQuadrado, std::string tipoQuadrado, std::vector<Coordenadas> coordenadas) : Retangulo(nomeQuadrado, tipoQuadrado, coordenadas){}
	~Quadrado(){}

	void desenhar(cairo_t* surf, std::vector<Coordenadas> coords);
private:
};


#endif /* INCLUDE_FORMAS_QUADRADO_HPP_ */
