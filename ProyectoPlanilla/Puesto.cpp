#include "Puesto.h"

Puesto::Puesto(const string& codigo, const string& nombre, double salarioBase) {
	this->codigo = codigo;
	this->nombre = nombre;
	this->salarioBase = salarioBase;
}

Puesto::~Puesto() {
}

string Puesto::getCodigo() const { return codigo; }
string Puesto::getNombre() const { return nombre; }
double Puesto::getSalarioBase() const { return salarioBase; }

void Puesto::setNombre(const string& nombre) { this->nombre = nombre; }
void Puesto::setSalarioBase(double salarioBase) { this->salarioBase = salarioBase; }
