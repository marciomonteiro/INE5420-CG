/*
 * Retangulo.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_FORMAS_RETANGULO_HPP_
#define INCLUDE_FORMAS_RETANGULO_HPP_

#include "../Objeto.hpp"

class Retangulo : public Objeto{
public:
	Retangulo(std::string nomeRetangulo, std::string tipoRetangulo, std::vector<Coordenadas> coordenadas) : Objeto(nomeRetangulo, tipoRetangulo, coordenadas){}
	~Retangulo(){}

	void desenhar();

private:
};


#endif /* INCLUDE_FORMAS_RETANGULO_HPP_ */
