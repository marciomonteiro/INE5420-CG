/*
 * Circulo.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_FORMAS_CIRCULO_HPP_
#define INCLUDE_FORMAS_CIRCULO_HPP_

#include "../Objeto.hpp"

class Circulo : public Objeto {
public:
	Circulo(std::string nome, std::string tipo, std::vector<Coordenadas> coordenadas) : Objeto(nome, tipo, coordenadas){}
	~Circulo(){}
	void desenhar(cairo_t* surf, std::vector<Coordenadas> coords);
};
#endif /* INCLUDE_FORMAS_CIRCULO_HPP_ */
