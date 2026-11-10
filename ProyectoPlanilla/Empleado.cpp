#include "Empleado.h"

Empleado::Empleado(const string& cedula, const string& nombre,
				   double salarioBase, double horasExtra) {
	this->cedula = cedula;
	this->nombre = nombre;
	this->salarioBase = salarioBase;
	this->horasExtra = horasExtra;
}

Empleado::~Empleado() {
}

string Empleado::getCedula() const { 
	return cedula; 
}
string Empleado::getNombre() const { 
	return nombre; 
}
double Empleado::getSalarioBase() const { 
	return salarioBase; 
}
double Empleado::getHorasExtra() const { 
	return horasExtra; 
}

void Empleado::setNombre(const string& nombre) { 
	this->nombre = nombre; 
}
void Empleado::setSalarioBase(double salarioBase) { 
	this->salarioBase = salarioBase; 
}
void Empleado::setHorasExtra(double horasExtra) { 
	this->horasExtra = horasExtra; 
}
