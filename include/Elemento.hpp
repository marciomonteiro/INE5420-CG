#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP

template<typename T>
class Elemento {
private:
	T *info;
	Elemento<T>* _next;

public:
	Elemento(const T& info, Elemento<T>* next);
	~Elemento();
	Elemento<T>* getProximo() const;
	T getInfo() const;
	void setProximo(Elemento<T>* next);
};

#endif
