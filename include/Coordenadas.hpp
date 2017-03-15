/*
 * Coordenadas.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_COORDENADAS_CPP_
#define INCLUDE_COORDENADAS_CPP_

class Coordenadas {
public:
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	void setAux(double aux);

	double getX();
	double getY();
	double getZ();
	double getAux();

private:
	double x;
	double y;
	double z;
	double aux;
};



#endif /* INCLUDE_COORDENADAS_CPP_ */