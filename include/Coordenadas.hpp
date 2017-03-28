/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Coordenadas.hpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	curse lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_COORDENADAS_HPP_
#define INCLUDE_COORDENADAS_HPP_

class Coordenadas {
private:
	double x;
	double y;
	double z;
	double aux;
public:
	Coordenadas(double xE, double yE, double zE, double auxE) : x(xE), y(yE), z(zE), aux(auxE) {};
	Coordenadas(){};
	~Coordenadas(){};

	void setX(double x){this->x=x;};
	void setY(double y){this->y=y;};
	void setZ(double z){this->z=z;};
	void setAux(double aux){this->aux=aux;};

	double getX(){x};
	double getY(){y};
	double getZ(){z};
	double getAux(){aux};
};
#endif /* INCLUDE_COORDENADAS_HPP_ */
