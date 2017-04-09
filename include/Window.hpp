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

class Window {
private:
	Coordenadas *inicioDaWindow, *fimDaWindow, *centroDaWindow;
	DisplayFile *displayfile;
	double anguloX, anguloY, anguloZ;
	void atualizaCentroDaWindow();
	Window();
	void clipaLinhaComCS(std::vector<Coordenadas>& coords);
	void clipaLinhaComLB(std::vector<Coordenadas>& coords);
	int determinaRCDeCoordenada(Coordenadas& c);
public:
	static Window& instancia();
	~Window(){};
	void setWindow(Coordenadas* inicio, Coordenadas* fim, DisplayFile * world);
	void novoAngulo(double x, double y, double z);
	void zoom(double porcentagem);
	void normalizaCoordenadasDoMundo();
	void mover(double x, double y, double z);
	void setCoordenadas(Coordenadas* inicio, Coordenadas* fim){inicioDaWindow = inicio; fimDaWindow = fim;}
	Coordenadas* getInicioDaWindow(){return inicioDaWindow;}
	Coordenadas* getFimDaWindow(){return fimDaWindow;}
	Coordenadas* getCentroDaWindow(){return centroDaWindow;}
	void setCoordsWindow(Coordenadas* inicio, Coordenadas* fim);	
	void clipaPonto(std::vector<Coordenadas>& coords);
	void clipaLinha(std::vector<Coordenadas>& coords);
	void clipaPoligono(std::vector<Coordenadas>& coords);
};
#endif /* INCLUDE_WINDOW_HPP_ */
