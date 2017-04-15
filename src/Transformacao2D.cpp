
#include "Transformacao2D.hpp"


std::vector<std::vector<double>>* Transformacao2D::translacao(double dx, double dy){
	std::vector<std::vector<double>> retorno {{1, 0, 0},{0, 1, 0},{dx, dy, 1}};
	return &retorno;
}

std::vector<std::vector<double>>* Transformacao2D::escalonamento(double sx, double sy){
	std::vector<std::vector<double>> retorno {{sx, 0, 0},{0, sy, 0},{0, 0, 1}};
	return &retorno;
}
std::vector<std::vector<double>>* Transformacao2D::rotacao(double graus){
	double radianos = (M_PI/180)*graus;
	std::vector<std::vector<double>> retorno {{cos(radianos), -sin(radianos), 0},{sin(radianos), cos(radianos), 0},{0, 0, 1}};
	return &retorno;
}