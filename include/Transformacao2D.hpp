/*
 * Transformacao2D.hpp
 *
 *  Created on: 20 de mar de 2017
 *      Author: Marcio
 */

#ifndef INCLUDE_TRANSFORMACAO2D_HPP_
#define INCLUDE_TRANSFORMACAO2D_HPP_

#include <iostream>
#include "Coordenadas.hpp"
#include <cmath>
#include <vector>
#include "Matriz.hpp"

class Transformacao2D {
public:

	//Transformacao2D(){};
	Transformacao2D(){}
	~Transformacao2D(){};

	std::vector<std::vector<double>> translacao(double dx, double dy);
	std::vector<std::vector<double>> escalonamento(double sx, double sy);
	std::vector<std::vector<double>> rotacao(double graus);

private:
};



#endif /* INCLUDE_TRANSFORMACAO2D_HPP_ */
