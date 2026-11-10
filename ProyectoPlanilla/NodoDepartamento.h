#ifndef NODODEPARTAMENTO_H
#define NODODEPARTAMENTO_H

#include <cstddef>
#include "Departamento.h"

class NodoDepartamento {
private:
	Departamento* dato;
	NodoDepartamento* siguiente;
	
public:
	NodoDepartamento(Departamento* dato);
	~NodoDepartamento();
	
	Departamento* getDato() const;
	NodoDepartamento* getSiguiente() const;
	void setSiguiente(NodoDepartamento* siguiente);
};

#endif
