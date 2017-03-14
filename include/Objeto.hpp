/*
 * Objeto.h
 *
 *  Created on: 13 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_OBJETO_HPP_
#define INCLUDE_OBJETO_HPP_

#include <string>
#include "Coordenadas.hpp"

using namespace std;

class Objeto : public Coordenadas{
private:
	string name, tipo;

public:

	Objeto(string name, string tipo){
		this->name = name;
		this->tipo = tipo;
		setCoordenadas(0,0,0,0);
	}

	~Objeto(){}

	void setCoordenadas(double x, double y, double z, double aux);
	void setCoordenadas2D(double x, double y);
	void setCoordenadas3D(double x, double y, double z);
	const string& getName() const;
	const string& getTipo() const;

};

#endif /* INCLUDE_OBJETO_HPP_ */
