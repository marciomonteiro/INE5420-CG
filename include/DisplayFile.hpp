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
 *	curse lectured in Federal University of Santa Catarina.
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
	void removeObjectFromTheWorld(std::string objName){objectsInTheWorld.erase(objName);};
	Objeto* getTheObjectFromTheWorld(std::string objName){return objectsInTheWorld.find(objName)->second;};
	std::unordered_map<std::string, Objeto* > getAllObjectsFromTheWorld(){return objectsInTheWorld;};
	bool isEmpty(){return objectsInTheWorld.empty();};
};
#endif //DISPLAYFILE_H
