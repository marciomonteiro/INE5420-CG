/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * Transformacao3D.cpp
 *
 *  Created on: 19 de abr de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_TRANSFORMACAO3D_HPP_
#define INCLUDE_TRANSFORMACAO3D_HPP_

#include "Matriz.hpp"
#include "Coordenadas.hpp"
#include <iostream>
#include <cmath>

namespace Transformacao3D {
	/**
	 * Realiza a translacao de um objeto 3D.
	 */
	Matriz::Matriz<double> translacao(double dx, double dy, double dz);

	/**
	 * Realiza o escalonamento de um objeto 3D.
	 */
	/*
	 * TO-DO
	 * Adicionar o centro e fazer as modificações.
	 */
	Matriz::Matriz<double> escalonamento(double sx, double sy, double sz);

	Matriz::Matriz<double> escalonamento_da_matriz(double sx, double sy, double sz);

	/**
	 * Realiza a rotacao de um objeto 3D.
	 */
	Matriz::Matriz<double> rotacao(double grauX, double grauY, double grauZ);

	/**
	 * Realiza a rotação 3D do eixo X de um objeto;
	 * \param grauX valor do grau em radianos
	 */
	Matriz::Matriz<double> rotacaoX(double grauX);

	/**
	 * Realiza a rotação 3D do eixo Y de um objeto;
	 * \param grauY valor do grau em radianos
	 */
	Matriz::Matriz<double> rotacaoY(double grauY);

	/**
	 * Realiza a rotação 3D do eixo Z de um objeto;
	 * \param grauZ valor do grau em radianos
	 */
	Matriz::Matriz<double> rotacaoZ(double grauZ);

	/**
	 * Realiza a rotacao de um objeto 3D em torno a um eixo arbitrario.
	 */
	Matriz::Matriz<double> rotacao_eixo_arbitrario(double grauX, double grauY, double grauZ, Coordenadas eixo);
};

#endif /* INCLUDE_TRANSFORMACAO3D_HPP_ */
