/*
 * Objeto.cpp
 *
 *  Created on: 14 de mar de 2017
 *      Author: rodrigo
 */

#include "Objeto.hpp"

const std::string Objeto::getName() const {
	return nome;
}

const std::string& Objeto::getTipo() const {
	return tipo;
}

void Objeto::setName(const std::string& name){
	this->nome = name;
}

void Objeto::setTipo(const std::string& tipo) {
	this->tipo = tipo;
}