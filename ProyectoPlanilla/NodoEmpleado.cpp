#include "NodoEmpleado.h"

NodoEmpleado::NodoEmpleado(Empleado* dato) {
	this->dato = dato;
	this->siguiente = NULL;
}

NodoEmpleado::~NodoEmpleado() {
}

Empleado* NodoEmpleado::getDato() const { return dato; }
NodoEmpleado* NodoEmpleado::getSiguiente() const { return siguiente; }
void NodoEmpleado::setSiguiente(NodoEmpleado* siguiente) { this->siguiente = siguiente; }
