#include "Departamento.h"

Departamento::Departamento(const string& codigo, const string& nombre) {
	this->codigo = codigo;
	this->nombre = nombre;
}

Departamento::~Departamento() {
}

string Departamento::getCodigo() const { return codigo; }
string Departamento::getNombre() const { return nombre; }
void Departamento::setNombre(const string& nombre) { this->nombre = nombre; }

void Departamento::agregarPuesto(Puesto* puesto) {
	puestos.insertarAlFinal(puesto);
}

Puesto* Departamento::buscarPuesto(const string& codigo) const {
	return puestos.buscarPorCodigo(codigo);
}

bool Departamento::eliminarPuesto(const string& codigo) {
	return puestos.eliminarPorCodigo(codigo);
}

Puesto* Departamento::obtenerPuestoEn(int indice) const {
	return puestos.obtenerEn(indice);
}

int Departamento::getCantidadPuestos() const {
	return puestos.getCantidad();
}
