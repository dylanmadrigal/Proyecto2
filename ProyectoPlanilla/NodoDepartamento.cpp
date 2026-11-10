#include "NodoDepartamento.h"

NodoDepartamento::NodoDepartamento(Departamento* dato) {
	this->dato = dato;
	this->siguiente = NULL;
}

NodoDepartamento::~NodoDepartamento() {
}

Departamento* NodoDepartamento::getDato() const { return dato; }
NodoDepartamento* NodoDepartamento::getSiguiente() const { return siguiente; }
void NodoDepartamento::setSiguiente(NodoDepartamento* siguiente) { this->siguiente = siguiente; }
