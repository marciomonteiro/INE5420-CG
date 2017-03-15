/*
 * Ponto.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_FORMAS_PONTO_HPP_
#define INCLUDE_FORMAS_PONTO_HPP_

#include "../Objeto.hpp"

class Ponto : public Objeto {
public:
	Ponto(string nome, string tipo = "Ponto", vector<Coordenadas> coordenadas) : Objeto(nome, tipo, coordenadas){
	}

	~Ponto(){}


private:
};


#endif /* INCLUDE_FORMAS_PONTO_HPP_ */
