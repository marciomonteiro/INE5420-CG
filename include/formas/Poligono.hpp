/*
 * Poligono.hpp
 *
 *  Created on: 13 de mar de 2017
 *      Author: rodrigo
 */

#ifndef INCLUDE_POLIGONO_HPP_
#define INCLUDE_POLIGONO_HPP_

#include "../Objeto.hpp"

class Poligono : public Objeto {
private:
	std::vector<Coordenadas> coordenadas; //vertices

public:

	Poligono(std::string nomePoligono, std::string tipoPoligono, std::vector<Coordenadas> coordenadas) : Objeto(nomePoligono, tipoPoligono, coordenadas){
	}

	~Poligono(){}



/**
	void polígono (Ponto *vertices, int n) { //Desenha um polígono de n vértices

		int i;

		for (i = 0; i < n - 1; i++) {
			linha (vertices[i].x, vertices[i].y, vertices[i +1].x, vertices[i +1].y);
		}
		linha (vertices[0].x, vertices[0].y, vertices[i].x, vertices[i].y);
	}
 */
};



#endif /* INCLUDE_POLIGONO_HPP_ */
