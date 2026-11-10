#ifndef NODOPUESTO_H
#define NODOPUESTO_H

#include <cstddef>
#include "Puesto.h"

class NodoPuesto {
private:
	Puesto* dato;
	NodoPuesto* siguiente;
	
public:
	NodoPuesto(Puesto* dato);
	~NodoPuesto();
	
	Puesto* getDato() const;
	NodoPuesto* getSiguiente() const;
	void setSiguiente(NodoPuesto* siguiente);
};

#endif
