/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $Window.hpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_WINDOW_HPP_
#define INCLUDE_WINDOW_HPP_

#include <iostream>
#include "DisplayFile.hpp"
#include "Coordenadas.hpp"
#include "Matriz.hpp"
#include "Transformacao2D.hpp"
#include "Transformacao3D.hpp"
#include "Vetor.hpp"

class Window {
private:
	Coordenadas *inicioDaWindow, *fimDaWindow, *centroDaWindow, *vrp;
	Vetor *vpn;
	DisplayFile *displayfile;
	double anguloX, anguloY, anguloZ;
	void atualizaCentroDaWindow();
	Window();

public:
	static Window& instancia();
	~Window(){};

	/**
	 * Define as coordenadas de inicio e fim da window, junto do seu display file.
	 * \param inicio coordenadas do inicio da window.
	 * \param fim coordenadas do fim da window.
	 * \param world ponteiro do mundo.
	 */
	void setWindow(Coordenadas* inicio, Coordenadas* fim, DisplayFile * world);

	/**
	 * Rotaciona a window dado os novos angulos.
	 * \param x rotaciona a window em x graus em torno do eixo x.
	 * \param y rotaciona a window em y graus em torno do eixo y.
	 * \param z rotaciona a window em z graus em torno do eixo z.
	 */
	void novoAngulo(double x, double y, double z);

	/**
	 * Funcao de zoom na window.
	 * \param porcentagem quantidade para dar o zoom.
	 */
	void zoom(double porcentagem);

	/**
	 * Normaliza as coordenadas do mundo.
	 */
	void normalizaCoordenadasDoMundo();

	/**
	 * Move a window alterando os valores x e y da coordenada da window.
	 */
	void mover(double x, double y, double z);

	/**
	 * Retorna as coordenadas do inicio da window.
	 */
	Coordenadas* getInicioDaWindow(){return inicioDaWindow;}

	/**
	 * Retorna as coordenadas do final da window.
	 */
	Coordenadas* getFimDaWindow(){return fimDaWindow;}

	/**
	 * Retorna as coordenadas do centro da window.
	 */
	Coordenadas* getCentroDaWindow(){return centroDaWindow;}

	/**
	 * Retorna as coordenadas da VRP.
	 */
	Coordenadas* get_vrp(){return vrp;}

	/**
	 * Retorna o vetor da VPN.
	 */
	Vetor* get_vpn(){return vpn;}

	/**
	 * Altera as coordenadas de inicio e fim da window.
	 */
	void setCoordsWindow(Coordenadas* inicio, Coordenadas* fim);

};
#endif /* INCLUDE_WINDOW_HPP_ */
