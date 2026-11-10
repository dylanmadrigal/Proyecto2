#include "ListaDepartamentos.h"

ListaDepartamentos::ListaDepartamentos() {
	primero = NULL;
	ultimo = NULL;
	cantidad = 0;
}

ListaDepartamentos::~ListaDepartamentos() {
	NodoDepartamento* actual = primero;
	while (actual != NULL) {
		NodoDepartamento* siguiente = actual->getSiguiente();
		delete actual->getDato();
		delete actual;
		actual = siguiente;
	}
}

void ListaDepartamentos::insertarAlFinal(Departamento* departamento) {
	NodoDepartamento* nuevo = new NodoDepartamento(departamento);
	if (primero == NULL) {
		primero = nuevo;
		ultimo = nuevo;
	} else {
		ultimo->setSiguiente(nuevo);
		ultimo = nuevo;
	}
	cantidad++;
}

Departamento* ListaDepartamentos::buscarPorCodigo(const string& codigo) const {
	NodoDepartamento* actual = primero;
	while (actual != NULL) {
		if (actual->getDato()->getCodigo() == codigo) {
			return actual->getDato();
		}
		actual = actual->getSiguiente();
	}
	return NULL;
}

bool ListaDepartamentos::eliminarPorCodigo(const string& codigo) {
	NodoDepartamento* anterior = NULL;
	NodoDepartamento* actual = primero;
	
	while (actual != NULL && actual->getDato()->getCodigo() != codigo) {
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

Departamento* ListaDepartamentos::obtenerEn(int indice) const {
	if (indice < 0 || indice >= cantidad) {
		return NULL;
	}
	NodoDepartamento* actual = primero;
	for (int i = 0; i < indice; i++) {
		actual = actual->getSiguiente();
	}
	return actual->getDato();
}

int ListaDepartamentos::getCantidad() const { return cantidad; }

bool ListaDepartamentos::estaVacia() const { return cantidad == 0; }
