/*
 * Objeto.h
 *
 *  Created on: 13 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_OBJETO_HPP_
#define INCLUDE_OBJETO_HPP_

#include <string>
#include <vector>
#include "Coordenadas.hpp"

class Objeto{
private:
	std::string nome, tipo;
	std::vector<Coordenadas> world_coordenadas;

protected:
	void setName(const std::string& name);
	void setTipo(const std::string& tipo);

public:
	Objeto(std::string nomeObjeto, std::string tipoObjeto, std::vector<Coordenadas> coordenadas) : nome(nomeObjeto), tipo(tipoObjeto), world_coordenadas(coordenadas){
	}

	~Objeto(){}

	const std::string& getName() const;
	const std::string& getTipo() const;
};

#endif /* INCLUDE_OBJETO_HPP_ */
