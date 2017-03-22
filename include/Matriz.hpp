/*
 * Matriz.hpp
 *
 *  Created on: 21 de mar de 2017
 *      Author: rodrigo
 */

/**
 * A ideia é criar uma matriz genérica
 */
#ifndef INCLUDE_MATRIZ_HPP_
#define INCLUDE_MATRIZ_HPP_
/*
template <unsigned linhas, unsigned colunas>	//Tem que ser sem sinal pra não dar pau.
class Matriz {
public:
	Matriz(){}
	~Matriz(){}

	Matriz<linhas, colunas> transponha(const Matriz<linhas, colunas>& matrizAux);
	auto getElementoNaPosicao(int linha, int coluna);

private:

};


template <unsigned linhas, unsigned colunas>
Matriz<colunas,linhas> transponha(const Matriz<linhas,colunas>& m) {
	Matriz<colunas,linhas> aux;
    for (auto i = 0; i < linhas; i++){
    	for (auto j = 0; j < colunas; j++){
    		aux(j,i) = m(i,j);
    	}
    }
      return aux;
}

template <unsigned linhas, unsigned colunas>
auto getElementoNaPosicao(int linha, int coluna){
	return Matriz<linha, coluna>;
}
*/

#include <stdexcept>
#include <vector>

// undefine to disable range checking
#define RANGE_CHECK

template<class T>
class Matriz {
   private:
      std::vector<T> elementos;
   public:
      const unsigned linha;
      const unsigned coluna;

   protected:
      // range check function for matrix access
      void range_check( unsigned i, unsigned j ) const;

   public:
      T& operator()( unsigned i, unsigned j ) {
         #ifdef RANGE_CHECK
         range_check(i,j);
         #endif
         return elementos[i*coluna+j];
      }

      const T& operator()( unsigned i, unsigned j ) const {
         #ifdef RANGE_CHECK
         range_check(i,j);
         #endif
         return elementos[i*coluna+j];
      }

      const T& element(unsigned i, unsigned j) const {
         #ifdef RANGE_CHECK
         range_check(i,j);
         #endif
         return elementos[i*coluna+j];
      }

      T& element(unsigned i, unsigned j) {
         #ifdef RANGE_CHECK
         range_check(i,j);
         #endif
         return elementos[i*coluna+j];
      }

   public:
      Matriz( unsigned rows, unsigned cols, const T* elements = 0 );
      Matriz( const Matriz<T>& );
      ~Matriz();

      // matrix multiplication
      Matriz<T> operator*( const Matriz<T>& ) const;
      Matriz<T>& operator*=( const Matriz<T>& M ) {
         return *this = *this * M;
      }

      // vector operations
      Matriz<T> getrow( unsigned j ) const;
      Matriz<T> getcol( unsigned i ) const;

      Matriz<T> transpose() const;
      Matriz<T> operator~() const {
         return transpose();
      }
};


template<class T>
Matriz<T>::Matriz( unsigned rows, unsigned cols, const T* elements = 0 ) : linha(rows), coluna(cols), elementos(rows*cols,T(0.0)){
   if( rows == 0 || cols == 0 )
      throw std::range_error("attempt to create a degenerate matrix");
   // initialze from array
   if(elements)
      for(unsigned i=0;i<rows*cols;i++)
         this->elementos[i] = elements[i];
};

template<class T>
Matriz<T>::Matriz( const Matriz<T>& cp ) : linha(cp.linha), coluna(cp.coluna), elementos(cp.elementos){
}

template<class T>
Matriz<T>::~Matriz()
{
}

template<class T>
void Matriz<T>::range_check( unsigned i, unsigned j ) const {
   if( linha <= i )
      throw std::range_error("matrix access row out of range");
   if( coluna <= j )
      throw std::range_error("matrix access col out of range");
}


#endif /* INCLUDE_MATRIZ_HPP_ */
