/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 *
 * $DisplayFile.hpp
 *
 *  Created on: $14 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 *
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include <iostream>
#include <unordered_map>
#include "Objeto.hpp"

class DisplayFile {
private:
	std::unordered_map<std::string, Objeto*> objectsInTheWorld;
public:
	DisplayFile(){};
	~DisplayFile(){};

	static DisplayFile& instancia();
	bool addObjectInTheWorld(Objeto* obj);
	void removeObjectFromTheWorld(std::string objName);
	bool objectExistsInTheWorld(std::string objName);
	Objeto* getTheObjectFromTheWorld(std::string objName);
	std::unordered_map<std::string, Objeto* > getAllObjectsFromTheWorld();
	bool isEmpty();
};
#endif //DISPLAYFILE_H
