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
	std::vector<double> retorno {1.0, 0.0, 0.0, 0.0,
								 0.0, 1.0, 0.0, 0.0,
								 0.0, 0.0, 1.0, 0.0,
								 dx, dy, dz, 1.0};
	return Matriz::Matriz<double>(4u,4u,retorno);
}

Matriz::Matriz<double> Transformacao3D::escalonamento(double sx, double sy, double sz){
	std::vector<double> retorno {sx, 0.0, 0.0, 0.0,
								 0.0, sy, 0.0, 0.0,
								 0.0, 0.0, sz, 0.0,
								 0.0, 0.0, 1.0};
	return Matriz::Matriz<double>(4u,4u,retorno);
}

Matriz::Matriz<double> escalonamento_da_matriz(double sx, double sy, double sz){
	std::vector<double> retorno {sx, 0.0, 0.0, 0.0,
								 0.0, sy, 0.0, 0.0,
								 0.0, 0.0, sz, 0.0,
								 0.0, 0.0, 1.0};
	return Matriz::Matriz<double>(4u,4u,retorno);
}

Matriz::Matriz<double> Transformacao3D::rotacao(double grauX, double grauY, double grauZ){
	Matriz::Matriz<double> rX = rotacaoX(grauX);
	Matriz::Matriz<double> rY = rotacaoY(grauY);
	rX = rX * rY;
	Matriz::Matriz<double> rZ = rotacaoZ(grauZ);
	return rX * rZ;
}

Matriz::Matriz<double> Transformacao3D::rotacaoX(double grauX){
	double radX = (M_PI/180.0)*grauX;
	std::vector<double> retornoX {1.0, 0.0, 0.0, 0.0,
								  0.0, cos(radX), sin(radX), 0.0,
								  0.0, -sin(radX), cos(radX), 0.0,
								  0.0, 0.0, 0.0, 1.0};
	return Matriz::Matriz<double>(4u,4u,retornoX);
}

Matriz::Matriz<double> Transformacao3D::rotacaoY(double grauY){
	double radY = (M_PI/180.0)*grauY;
	std::vector<double> retornoY {cos(radY), 0.0, -sin(radY), 0.0,
								  0.0, 1.0, 0.0, 0.0,
								  sin(radY), 0.0, cos(radY), 0.0,
								  0.0, 0.0, 0.0, 1.0};
	return Matriz::Matriz<double>(4u,4u,retornoY);
}

Matriz::Matriz<double> Transformacao3D::rotacaoZ(double grauZ){
	double radZ = (M_PI/180.0)*grauZ;
	std::vector<double> retornoZ {cos(radZ), sin(radZ), 0.0, 0.0,
								  -sin(radZ), cos(radZ), 0.0, 0.0,
								  0.0, 0.0, 1.0, 0.0,
								  0.0, 0.0, 0.0, 1.0};
	return Matriz::Matriz<double>(4u,4u,retornoZ);
}

//
// precisa ser feito isso
//
// Matriz::Matriz<double> rotacao_eixo_arbitrario(double grauX, double grauY, double grauZ, Coordenadas eixo){
// 	double d = sqrt(eixo.getY()*eixo.getY() + eixo.getZ()*eixo.getZ());
// 	double alfa = atan(eixo.getX()/eixo.getY());
// 	double beta = atan(eixo.getY()/d);
// 	// double matriz_aux = Transformacao3D::rotacaoY(-beta) * Transformacao3D::rotacaoX(alfa);
// 	// matriz_aux = matriz_aux * Transformacao3D::rotacao(grauX, grauY, grauZ);
// 	// matriz_aux = matriz_aux * Transformacao3D::rotacaoX(-alfa);
// 	// matriz_aux = matriz_aux * Transformacao3D::rotacaoY(beta);
// 	// matriz_aux = matriz_aux * Transformacao3D::translacao(eixo.getX(), eixo.getY(), eixo.getZ());
// 	Matriz::Matriz<double> matriz_auxRotY = Transformacao3D::rotacaoY(-beta);
// 	Matriz::Matriz<double> matriz_auxRotX = Transformacao3D::rotacaoX(alfa);
// 	Matriz::Matriz<double> matriz_auxRot = Transformacao3D::rotacao(grauX, grauY, grauZ);
// 	Matriz::Matriz<double> matriz_auxRotXAlfa = Transformacao3D::rotacaoX(-alfa);
// 	Matriz::Matriz<double> matriz_auxRotYBeta = Transformacao3D::rotacaoY(beta);
// 	Matriz::Matriz<double> matriz_auxTrans = Transformacao3D::translacao(eixo.getX(), eixo.getY(), eixo.getZ());
// 	matriz_auxRotY = matriz_auxRotY * matriz_auxRotX;
// 	matriz_auxRotY = matriz_auxRotY * matriz_auxRot;
// 	matriz_auxRotY = matriz_auxRotY * matriz_auxRotXAlfa;
// 	matriz_auxRotY = matriz_auxRotY * matriz_auxRotYBeta;
// 	matriz_auxRotY = matriz_auxRotY * matriz_auxTrans;
// 	Matriz::Matriz<double> dz = -eixo.getZ() * matriz_auxRotY;
// 	return Transformacao3D::translacao(-eixo.getX(), -eixo.getY(), dz);
// }
