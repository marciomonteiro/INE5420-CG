/*
 *	================================================
 *		FEDERAL UNIVERSITY OF SANTA CATARINA
 *	================================================
 * 
 * DescritorOBJ.hpp
 *
 *  Created on: 27 de mar de 2017.
 *     Authors: Marcio Monteiro and Rodrigo Pedro Marques.
 *	    GitHub: https://github.com/marciomonteiro/INE5420-CG.git
 *	 Professor: Dr. rer.nat. Aldo von Wangenheim
 * 	
 *	This file is part of a project for the INE5420 Computer Graphics
 *	course lectured in Federal University of Santa Catarina.
 */

#ifndef INCLUDE_DESCRITOROBJ_HPP_
#define INCLUDE_DESCRITOROBJ_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include "Objeto.hpp"

class DescritorOBJ {
public:

	DescritorOBJ() : extensao(".obj"), pathRoot("./objetos/"){}
	~DescritorOBJ(){}

	bool transcrevaObjeto(Objeto* obj);
	Objeto* leiaObjetoFromPath(std::string pathToObject);
	std::vector<std::string> getObjetosFromPath(std::string pathToObjects);

private:
	std::string extensao;
	std::string pathRoot;
};



#endif /* INCLUDE_DESCRITOROBJ_HPP_ */
