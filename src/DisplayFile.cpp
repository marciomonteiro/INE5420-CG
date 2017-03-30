/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $DisplayFile.cpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#include "DisplayFile.hpp"

DisplayFile& DisplayFile::instancia(){
	static DisplayFile instancia;
	return instancia;
}

bool DisplayFile::addObjectInTheWorld(Objeto* obj){
	if(!objectsInTheWorld.insert(std::make_pair(obj->getName(),obj)).second){
      return false;
	}
    return true;
}
