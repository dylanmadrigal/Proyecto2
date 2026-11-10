#include "NodoPuesto.h"

NodoPuesto::NodoPuesto(Puesto* dato) {
	this->dato = dato;
	this->siguiente = NULL;
}

NodoPuesto::~NodoPuesto() {
}

Puesto* NodoPuesto::getDato() const { return dato; }
NodoPuesto* NodoPuesto::getSiguiente() const { return siguiente; }
void NodoPuesto::setSiguiente(NodoPuesto* siguiente) { this->siguiente = siguiente; }
