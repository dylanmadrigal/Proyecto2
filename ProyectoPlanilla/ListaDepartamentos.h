#ifndef LISTADEPARTAMENTOS_H
#define LISTADEPARTAMENTOS_H

#include "NodoDepartamento.h"

class ListaDepartamentos {
private:
	NodoDepartamento* primero;
	NodoDepartamento* ultimo;
	int cantidad;
	
	ListaDepartamentos(const ListaDepartamentos& otra);
	ListaDepartamentos& operator=(const ListaDepartamentos& otra);
	
public:
	ListaDepartamentos();
	~ListaDepartamentos();
	
	void insertarAlFinal(Departamento* departamento);
	Departamento* buscarPorCodigo(const string& codigo) const;
	bool eliminarPorCodigo(const string& codigo);
	Departamento* obtenerEn(int indice) const;
	int getCantidad() const;
	bool estaVacia() const;
};

#endif
