#include "ListaPuestos.h"

ListaPuestos::ListaPuestos() {
	primero = NULL;
	ultimo = NULL;
	cantidad = 0;
}

ListaPuestos::~ListaPuestos() {
	NodoPuesto* actual = primero;
	while (actual != NULL) {
		NodoPuesto* siguiente = actual->getSiguiente();
		delete actual->getDato();
		delete actual;
		actual = siguiente;
	}
}

void ListaPuestos::insertarAlFinal(Puesto* puesto) {
	NodoPuesto* nuevo = new NodoPuesto(puesto);
	if (primero == NULL) {
		primero = nuevo;
		ultimo = nuevo;
	} else {
		ultimo->setSiguiente(nuevo);
		ultimo = nuevo;
	}
	cantidad++;
}

Puesto* ListaPuestos::buscarPorCodigo(const string& codigo) const {
	NodoPuesto* actual = primero;
	while (actual != NULL) {
		if (actual->getDato()->getCodigo() == codigo) {
			return actual->getDato();
		}
		actual = actual->getSiguiente();
	}
	return NULL;
}

bool ListaPuestos::eliminarPorCodigo(const string& codigo) {
	NodoPuesto* anterior = NULL;
	NodoPuesto* actual = primero;
	
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

Puesto* ListaPuestos::obtenerEn(int indice) const {
	if (indice < 0 || indice >= cantidad) {
		return NULL;
	}
	NodoPuesto* actual = primero;
	for (int i = 0; i < indice; i++) {
		actual = actual->getSiguiente();
	}
	return actual->getDato();
}

int ListaPuestos::getCantidad() const { return cantidad; }

bool ListaPuestos::estaVacia() const { return cantidad == 0; }
