#ifndef NODOCOMPROBANTE_H
#define NODOCOMPROBANTE_H

#include <cstddef>
#include "ComprobantePago.h"

class NodoComprobante {
private:
	ComprobantePago* dato;
	NodoComprobante* siguiente;
	
public:
	NodoComprobante(ComprobantePago* dato);
	~NodoComprobante();
	
	ComprobantePago* getDato() const;
	NodoComprobante* getSiguiente() const;
	void setSiguiente(NodoComprobante* siguiente);
};

#endif
