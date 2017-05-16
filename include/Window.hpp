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
	void normalizaCoordenadasDoMundo();
	void mover(double x, double y, double z);
	void setCoordenadas(Coordenadas* inicio, Coordenadas* fim){inicioDaWindow = inicio; fimDaWindow = fim;}
	Coordenadas* getInicioDaWindow(){return inicioDaWindow;}
	Coordenadas* getFimDaWindow(){return fimDaWindow;}
	Coordenadas* getCentroDaWindow(){return centroDaWindow;}
	Coordenadas* get_vrp(){return vrp;}
	Vetor* get_vpn(){return vpn;}
	void setCoordsWindow(Coordenadas* inicio, Coordenadas* fim);

};
#endif /* INCLUDE_WINDOW_HPP_ */
