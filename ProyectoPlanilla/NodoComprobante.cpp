#include "NodoComprobante.h"

NodoComprobante::NodoComprobante(ComprobantePago* dato) {
	this->dato = dato;
	this->siguiente = NULL;
}

NodoComprobante::~NodoComprobante() {
}

ComprobantePago* NodoComprobante::getDato() const { return dato; }
NodoComprobante* NodoComprobante::getSiguiente() const { return siguiente; }
void NodoComprobante::setSiguiente(NodoComprobante* siguiente) { this->siguiente = siguiente; }
