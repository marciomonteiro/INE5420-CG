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
#include "../src/Coordenadas.cpp"

using namespace std;

class Objeto : public Coordenadas{
private:
	string nome, tipo;
	vector<Coordenadas> world_coordenadas;

protected:
	void setName(const string& name);
	void setTipo(const string& tipo);

public:
	Objeto(string nomeObjeto, string tipoObjeto, vector<Coordenadas> coordenadas) : nome(nomeObjeto), tipo(tipoObjeto), world_coordenadas(coordenadas){
	}

	~Objeto(){}

	void setCoordenadas(double x, double y, double z, double aux);
	void setCoordenadas2D(double x, double y);
	void setCoordenadas3D(double x, double y, double z);
	const string& getName() const;
	const string& getTipo() const;
};

#endif /* INCLUDE_OBJETO_HPP_ */