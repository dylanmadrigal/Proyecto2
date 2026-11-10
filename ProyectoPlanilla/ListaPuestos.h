#ifndef LISTAPUESTOS_H
#define LISTAPUESTOS_H

#include "NodoPuesto.h"

class ListaPuestos {
private:
	NodoPuesto* primero;
	NodoPuesto* ultimo;
	int cantidad;
	
	ListaPuestos(const ListaPuestos& otra);
	ListaPuestos& operator=(const ListaPuestos& otra);
	
public:
	ListaPuestos();
	~ListaPuestos();
	
	void insertarAlFinal(Puesto* puesto);
	Puesto* buscarPorCodigo(const string& codigo) const;
	bool eliminarPorCodigo(const string& codigo);
	Puesto* obtenerEn(int indice) const;
	int getCantidad() const;
	bool estaVacia() const;
};

#endif
