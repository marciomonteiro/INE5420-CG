/*
 * Elemento.cpp
 *
 *  Created on: 13 de mar de 2017
 *      Author: rodrigo
 */

#include "include/Elemento.hpp"

template<typename T>
inline Elemento<T>::Elemento(const T& info, Elemento<T>* next) : info(new T(info)), _next(next) {

}

template<typename T>
inline Elemento<T>::~Elemento() {
	delete info;
}

template<typename T>
inline Elemento<T>* Elemento<T>::getProximo() const {
	return _next;
}

template<typename T>
inline T Elemento<T>::getInfo() const {
	return *info;
}

template<typename T>
inline void Elemento<T>::setProximo(Elemento<T>* next) {
	_next = next;
}
