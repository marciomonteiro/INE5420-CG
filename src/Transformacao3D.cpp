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

#include "../include/Transformacao3D.hpp"

Matriz::Matriz<double> Transformacao3D::translacao(double dx, double dy, double dz){
	std::cout<<"TO DO\nTransformacao3D::translacao"<<std::endl;
	std::vector<double> retorno {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	return Matriz::Matriz<double>(3u,3u,retorno);
}

Matriz::Matriz<double> Transformacao3D::escalonamento(double sx, double sy, double sz){
	std::cout<<"TO DO\nTransformacao3D::escalonamento"<<std::endl;
	std::vector<double> retorno {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	return Matriz::Matriz<double>(3u,3u,retorno);
}

Matriz::Matriz<double> Transformacao3D::rotacao(double grauX, double grauY, double grauZ, Coordenadas eixoArbitrario){
	std::cout<<"TO DO\nTransformacao3D::rotacao"<<std::endl;
	std::vector<double> retorno {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	return Matriz::Matriz<double>(3u,3u,retorno);
}