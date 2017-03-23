/*
 * Objeto.hpp
 *
 *  Created on: 13 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_OBJETO_HPP_
#define INCLUDE_OBJETO_HPP_

#include <iostream>
#include <gtk/gtk.h>
#include <string>
#include <vector>
#include "Coordenadas.hpp"
#include "Matriz.hpp"

class Objeto{
private:
	std::string nome, tipo;
	std::vector<Coordenadas> world_coordenadas;
protected:
	void setName(std::string& name);
	void setTipo(const std::string& tipo);
public:
	Objeto(std::string nomeObjeto, std::string tipoObjeto, std::vector<Coordenadas> coordenadas) : nome(nomeObjeto), tipo(tipoObjeto), world_coordenadas(coordenadas){}
	virtual ~Objeto(){}
 	std::string getName();
	const std::string& getTipo() const;
	std::vector<Coordenadas>* getCoordenadas(){return &world_coordenadas;}
	virtual void desenhar(cairo_t* surf, std::vector<Coordenadas> coords) = 0;	//=0 obriga implementar desenhar
	void transformaObjeto(Matriz::Matriz<double> matriz);
	Coordenadas centroDoObjeto();
};
#endif /* INCLUDE_OBJETO_HPP_ */