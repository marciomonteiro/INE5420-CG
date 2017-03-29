/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 * 
 * DescritorOBJ.cpp
 *
 *  Created on: 27 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 * 	
 *	This file is part of a project for the INE5420 Computer Graphics
 *	curse lectured in Federal University of Santa Catarina. 
 */

#include "../include/DescritorOBJ.hpp"

bool DescritorOBJ::transcrevaObjeto(Objeto* obj){
	std::string objectPath = pathRoot;		// "../objetos/"
	std::string nomeObj = obj->getName();	// "linha"
	nomeObj.append(extensao);				// "linha.obj"
	objectPath.append(nomeObj);				// "../objetos/linha.obj"

	if(std::ifstream(objectPath)){
		std::cout << "Arquivo " << nomeObj << " ja existe! " << std::endl;
		return false;
	}

	std::ofstream(objeto());

	return true;
}