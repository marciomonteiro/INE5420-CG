/*
 * Objeto.h
 *
 *  Created on: 13 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_OBJETO_HPP_
#define INCLUDE_OBJETO_HPP_

#include <string>

using namespace std;

template<typename T>
class Objeto {
private:
	string name, tipo;
	double x, y, z, aux;	//coordenadas

public:

	Objeto(string name, string tipo){
		this->name = name;
		this->tipo = tipo;
		setCoordenadas(0,0,0,0);
	}

	~Objeto(){}

	void setCoordenadas(double x, double y, double z, double aux){
		this->x = x;
		this->y = y;
		this->z = z;
		this->aux = aux;
	}

	void setCoordenadas2D(double x, double y){
		this->x = x;
		this->y = y;
		this->z = 0;
		this->aux = 0;
	}

	double getAux() const {
		return aux;
	}

	void setAux(double aux) {
		this->aux = aux;
	}

	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}

	const string& getTipo() const {
		return tipo;
	}

	void setTipo(const string& tipo) {
		this->tipo = tipo;
	}

	double getX() const {
		return x;
	}

	void setX(double x) {
		this->x = x;
	}

	double getY() const {
		return y;
	}

	void setY(double y) {
		this->y = y;
	}

	double getZ() const {
		return z;
	}

	void setZ(double z) {
		this->z = z;
	}
};

#endif /* INCLUDE_OBJETO_HPP_ */
