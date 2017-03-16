/*
 * Linha.hpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_FORMAS_LINHA_HPP_
#define INCLUDE_FORMAS_LINHA_HPP_

#include "../Objeto.hpp"

class Linha : public Objeto {
public:
	Linha(std::string nomeLinha, std::string tipoLinha, std::vector<Coordenadas> coordenadas) : Objeto(nomeLinha, tipoLinha, coordenadas){}
	~Linha(){}

private:
};


#endif /* INCLUDE_FORMAS_LINHA_HPP_ */

/*
 * Rascunho:
 * Uma linha pode ser uma reta ou ter várias curvas,
 * logo é necessário ter várias coordenadas, um conjunto de coordenadas.
 */
