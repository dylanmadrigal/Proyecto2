#ifndef LISTAEMPLEADOS_H
#define LISTAEMPLEADOS_H

#include "NodoEmpleado.h"

class ListaEmpleados {
private:
	NodoEmpleado* primero;
	NodoEmpleado* ultimo;
	int cantidad;
	
	ListaEmpleados(const ListaEmpleados& otra);
	ListaEmpleados& operator=(const ListaEmpleados& otra);
	
public:
	ListaEmpleados();
	~ListaEmpleados();
	
	void insertarAlFinal(Empleado* empleado);
	Empleado* buscarPorCedula(const string& cedula) const;
	bool eliminarPorCedula(const string& cedula);
	Empleado* obtenerEn(int indice) const;
	int getCantidad() const;
	bool estaVacia() const;
};

#endif
