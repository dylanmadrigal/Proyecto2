#ifndef NODOEMPLEADO_H
#define NODOEMPLEADO_H

#include <cstddef>
#include "Empleado.h"

class NodoEmpleado {
private:
	Empleado* dato;
	NodoEmpleado* siguiente;
	
public:
	NodoEmpleado(Empleado* dato);
	~NodoEmpleado();
	
	Empleado* getDato() const;
	NodoEmpleado* getSiguiente() const;
	void setSiguiente(NodoEmpleado* siguiente);
};

#endif
