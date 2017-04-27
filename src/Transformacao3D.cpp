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
	std::vector<double> retorno {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, dx, dy, dz, 1.0};
	return Matriz::Matriz<double>(4u,4u,retorno);
}

Matriz::Matriz<double> Transformacao3D::escalonamento(double sx, double sy, double sz){
	std::cout<<"TO DO\nTransformacao3D::escalonamento"<<std::endl;
	std::vector<double> retorno {sx, 0.0, 0.0, 0.0, 0.0, sy, 0.0, 0.0, 0.0, 0.0, sz, 0.0, 0.0, 0.0, 1.0};
	return Matriz::Matriz<double>(4u,4u,retorno);
}

Matriz::Matriz<double> Transformacao3D::rotacao(double grauX, double grauY, double grauZ, Coordenadas eixoArbitrario){
	std::cout<<"TO DO\nTransformacao3D::rotacao"<<std::endl;
	double radX = (M_PI/180.0)*grauX;
	double radY = (M_PI/180.0)*grauY;
	double radZ = (M_PI/180.0)*grauZ;
	std::vector<double> retornoX {1, 0.0, 0.0, 0.0, 0.0, cos(radX), sin(radX), 0.0, 0.0, -sin(radX), cos(radX), 0.0, 0.0, 0.0, 0.0, 1.0};
	std::vector<double> retornoY {cos(grauY), 0.0, -sin(grauY), 0.0, 0.0, 1.0, 0.0, 0.0, sin(grauY), 0.0, cos(grauY), 0.0, 0.0, 0.0, 0.0, 1.0};
	std::vector<double> retornoZ {cos(grauZ), sin(grauZ), 0.0, 0.0, -sin(grauZ), cos(grauZ), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
	Matriz::Matriz<double> rX = Matriz::Matriz<double>(4u,4u,retornoX);
	Matriz::Matriz<double> rY = Matriz::Matriz<double>(4u,4u,retornoY);
	Matriz::Matriz<double> rZ = Matriz::Matriz<double>(4u,4u,retornoZ);
	return dummy;
}

Matriz::Matriz<double> Transformacao3D::rotacaoX(double grauX){
	std::cout<<"TO DO\nTransformacao3D::rotacaoX"<<std::endl;
	double radX = (M_PI/180.0)*grauX;
	std::vector<double> retornoX {1, 0.0, 0.0, 0.0, 0.0, cos(radX), sin(radX), 0.0, 0.0, -sin(radX), cos(radX), 0.0, 0.0, 0.0, 0.0, 1.0};
	return Matriz::Matriz<double>(4u,4u,retornoX);
}

Matriz::Matriz<double> Transformacao3D::rotacaoY(double grauY){
	std::cout<<"TO DO\nTransformacao3D::rotacaoY"<<std::endl;
	double radY = (M_PI/180.0)*grauY;
	std::vector<double> retornoY {cos(grauY), 0.0, -sin(grauY), 0.0, 0.0, 1.0, 0.0, 0.0, sin(grauY), 0.0, cos(grauY), 0.0, 0.0, 0.0, 0.0, 1.0};
	return Matriz::Matriz<double>(4u,4u,retornoY);
}

Matriz::Matriz<double> Transformacao3D::rotacaoZ(double grauZ){
	std::cout<<"TO DO\nTransformacao3D::rotacaoZ"<<std::endl;
	double radZ = (M_PI/180.0)*grauZ;
	std::vector<double> retornoZ {cos(grauZ), sin(grauZ), 0.0, 0.0, -sin(grauZ), cos(grauZ), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
	return Matriz::Matriz<double>(4u,4u,retornoZ);
}
