/*
 * Matriz.hpp
 *
 *  Created on: 21 de mar de 2017
 *      Author: rodrigo
 */

/**
 * A ideia é criar uma matriz genérica
 */
#ifndef INCLUDE_MATRIZ_HPP_
#define INCLUDE_MATRIZ_HPP_

template <unsigned linhas, unsigned colunas>	//Tem que ser sem sinal pra não dar pau.
class Matriz {
public:
	Matriz(){}
	~Matriz(){}

	Matriz<linhas, colunas> transponha(const Matriz<linhas, colunas>& matrizAux);

private:
};


template <unsigned linhas, unsigned colunas>
Matriz<colunas,linhas> transponha(const Matriz<linhas,colunas>& m) {
	Matriz<colunas,linhas> aux;
    for (auto i = 0; i < linhas; i++){
    	for (auto j = 0; j < colunas; j++){
    		aux(j,i) = m(i,j);
    	}
    }
      return aux;
}

#endif /* INCLUDE_MATRIZ_HPP_ */
