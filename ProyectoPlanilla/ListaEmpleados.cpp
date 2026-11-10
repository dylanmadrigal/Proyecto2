#include "ListaEmpleados.h"

ListaEmpleados::ListaEmpleados() {
	primero = NULL;
	ultimo = NULL;
	cantidad = 0;
}

ListaEmpleados::~ListaEmpleados() {
	NodoEmpleado* actual = primero;
	while (actual != NULL) {
		NodoEmpleado* siguiente = actual->getSiguiente();
		delete actual->getDato();
		delete actual;
		actual = siguiente;
	}
}

void ListaEmpleados::insertarAlFinal(Empleado* empleado) {
	NodoEmpleado* nuevo = new NodoEmpleado(empleado);
	if (primero == NULL) {
		primero = nuevo;
		ultimo = nuevo;
	} else {
		ultimo->setSiguiente(nuevo);
		ultimo = nuevo;
	}
	cantidad++;
}

Empleado* ListaEmpleados::buscarPorCedula(const string& cedula) const {
	NodoEmpleado* actual = primero;
	while (actual != NULL) {
		if (actual->getDato()->getCedula() == cedula) {
			return actual->getDato();
		}
		actual = actual->getSiguiente();
	}
	return NULL;
}

bool ListaEmpleados::eliminarPorCedula(const string& cedula) {
	NodoEmpleado* anterior = NULL;
	NodoEmpleado* actual = primero;
	
	while (actual != NULL && actual->getDato()->getCedula() != cedula) {
		anterior = actual;
		actual = actual->getSiguiente();
	}
	
	if (actual == NULL) {
		return false;
	}
	
	if (anterior == NULL) {
		primero = actual->getSiguiente();
	} else {
		anterior->setSiguiente(actual->getSiguiente());
	}
	
	if (actual == ultimo) {
		ultimo = anterior;
	}
	
	delete actual->getDato();
	delete actual;
	cantidad--;
	return true;
}

Empleado* ListaEmpleados::obtenerEn(int indice) const {
	if (indice < 0 || indice >= cantidad) {
		return NULL;
	}
	NodoEmpleado* actual = primero;
	for (int i = 0; i < indice; i++) {
		actual = actual->getSiguiente();
	}
	return actual->getDato();
}

int ListaEmpleados::getCantidad() const { return cantidad; }

bool ListaEmpleados::estaVacia() const { return cantidad == 0; }
