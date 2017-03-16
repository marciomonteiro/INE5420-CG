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

class Objeto : public Coordenadas{
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

	void setCoordenadas(double x, double y, double z, double aux);
	void setCoordenadas2D(double x, double y);
	void setCoordenadas3D(double x, double y, double z);
	const std::string& getName() const;
	const std::string& getTipo() const;
};

#endif /* INCLUDE_OBJETO_HPP_ */
