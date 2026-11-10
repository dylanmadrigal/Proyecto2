#include "ListaComprobantes.h"

ListaComprobantes::ListaComprobantes() {
	primero = NULL;
	ultimo = NULL;
	cantidad = 0;
}

ListaComprobantes::~ListaComprobantes() {
	NodoComprobante* actual = primero;
	while (actual != NULL) {
		NodoComprobante* siguiente = actual->getSiguiente();
		delete actual->getDato();
		delete actual;
		actual = siguiente;
	}
}

void ListaComprobantes::insertarAlFinal(ComprobantePago* comprobante) {
	NodoComprobante* nuevo = new NodoComprobante(comprobante);
	if (primero == NULL) {
		primero = nuevo;
		ultimo = nuevo;
	} else {
		ultimo->setSiguiente(nuevo);
		ultimo = nuevo;
	}
	cantidad++;
}

ComprobantePago* ListaComprobantes::buscarPorCodigo(const string& codigo) const {
	NodoComprobante* actual = primero;
	while (actual != NULL) {
		if (actual->getDato()->getCodigo() == codigo) {
			return actual->getDato();
		}
		actual = actual->getSiguiente();
	}
	return NULL;
}

bool ListaComprobantes::eliminarPorCodigo(const string& codigo) {
	NodoComprobante* anterior = NULL;
	NodoComprobante* actual = primero;
	
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

ComprobantePago* ListaComprobantes::obtenerEn(int indice) const {
	if (indice < 0 || indice >= cantidad) {
		return NULL;
	}
	NodoComprobante* actual = primero;
	for (int i = 0; i < indice; i++) {
		actual = actual->getSiguiente();
	}
	return actual->getDato();
}

int ListaComprobantes::getCantidad() const { return cantidad; }

bool ListaComprobantes::estaVacia() const { return cantidad == 0; }

bool ListaComprobantes::existenDeEmpleado(const string& cedula) const {
	NodoComprobante* actual = primero;
	while (actual != NULL) {
		if (actual->getDato()->getEmpleado()->getCedula() == cedula) {
			return true;
		}
		actual = actual->getSiguiente();
	}
	return false;
}

bool ListaComprobantes::existenDeDepartamento(const string& codigo) const {
	NodoComprobante* actual = primero;
	while (actual != NULL) {
		if (actual->getDato()->getDepartamento()->getCodigo() == codigo) {
			return true;
		}
		actual = actual->getSiguiente();
	}
	return false;
}
