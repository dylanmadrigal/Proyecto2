#ifndef LISTACOMPROBANTES_H
#define LISTACOMPROBANTES_H

#include "NodoComprobante.h"

class ListaComprobantes {
private:
	NodoComprobante* primero;
	NodoComprobante* ultimo;
	int cantidad;
	
	ListaComprobantes(const ListaComprobantes& otra);
	ListaComprobantes& operator=(const ListaComprobantes& otra);
	
public:
	ListaComprobantes();
	~ListaComprobantes();
	
	void insertarAlFinal(ComprobantePago* comprobante);
	ComprobantePago* buscarPorCodigo(const string& codigo) const;
	bool eliminarPorCodigo(const string& codigo);
	ComprobantePago* obtenerEn(int indice) const;
	int getCantidad() const;
	bool estaVacia() const;
	
	bool existenDeEmpleado(const string& cedula) const;
	bool existenDeDepartamento(const string& codigo) const;
};

#endif
