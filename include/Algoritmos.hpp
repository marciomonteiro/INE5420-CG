/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 * 
 * Algoritmos.hpp
 *
 *  Created on: 12 de abr de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 * 	
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina. 
 */

#ifndef INCLUDE_ALGORITMOS_HPP_
#define INCLUDE_ALGORITMOS_HPP_

#include <iostream>
#include <vector>
#include "Coordenadas.hpp"

namespace Algoritmos {

	static bool clipaMetodo = true;
	/**
	 * Algoritmo para clipagem de ponto.
	 * \param coords Coordenadas do ponto a ser clipado
	 */
	void clipaPonto(std::vector<Coordenadas>& coords);

	/**
	 * Algoritmo para clipagem de linha.
	 * \param coords Coordenadas da linha a ser clipada.
	 * \param clipaComCs valor booleano para definir se clipa com o algoritmo
	 * CS ou LB.
	 */
	void clipaLinha(std::vector<Coordenadas>& coords);

	/**
	 * Algoritmo para clipar poligonos.
	 * \param coords vetor de coordenadas do poligono.
	 */
	void clipaPoligono(std::vector<Coordenadas>& coords);

	/**
	 * Algoritmo de clipagem de linha com Cohen-Sutherland.
	 * \param coords coordenadas da linha a ser clipada.
	 */
	void clipaLinhaComCS(std::vector<Coordenadas>& coords);

	/**
	 * Algoritmo de clippagem de linha com Liang-Barsky.
	 * \param coords Coordenadas da linha.
	 */
	void clipaLinhaComLB(std::vector<Coordenadas>& coords);

	/**
	 * Verifica se um dado ponto esta fora da Window. Caso positivo,
	 * ele eh movido para a borda da window.
	 * \param c coordenadas do ponto.
	 */
	void pontoNoCanto(Coordenadas& c);

	/**
	 * Verifica se duas coordenadas sao iguais.
	 * \param coord1 coordenada um a ser comparada.
	 * \param coord2 coordenada dois a ser compara com a coord1.
	 * \return true se ambas forem iguais, false caso contrario.
	 */
	bool comparaCoordenadas(Coordenadas coord1, Coordenadas coord2);

	/**
	 * Detertemina o Region Code de uma dada coordenada.
	 * \param c coordenadas a ter seu RC determinado.
	 * \return int valor do Region Code da coordenada.
	 */
	int determinaRCDeCoordenada(Coordenadas& c);

	/**
	 * Define o algoritmo de clipagem de reta.
	 * \param v valor booleano que define se sera usado CS ou nao.
	 */
	void setaMetodoClippingReta(bool v);

	/**
	 * Algoritmo de clipagem de curva.
	 * \param coords vetor de coordenadas da curva a ser clipada.
	 */
	void clipaCurva(std::vector<Coordenadas>& coords);

}  // namespace Algoritmos

#endif /* INCLUDE_ALGORITMOS_HPP_ */