/*
 * Objeto.hpp
 *
 *  Created on: 13 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_OBJETO_HPP_
#define INCLUDE_OBJETO_HPP_

#include <string>
#include <vector>
#include <gtk/gtk.h>
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

	virtual ~Objeto(){}

	const std::string& getName() const;
	const std::string& getTipo() const;
	virtual void desenhar() = 0;	//=0 obriga implementar desenhar
};

#endif /* INCLUDE_OBJETO_HPP_ */
