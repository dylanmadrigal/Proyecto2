#ifndef GESTORDEPARTAMENTOS_H
#define GESTORDEPARTAMENTOS_H

#include <string>
#include "ListaDepartamentos.h"
#include "ListaComprobantes.h"
#include "PersistenciaArchivos.h"
#include "Validaciones.h"

using namespace std;

class GestorDepartamentos {
private:
	ListaDepartamentos* departamentos;
	ListaComprobantes* comprobantes;
	PersistenciaArchivos* persistencia;
	Validaciones* validador;
	
	string guardar() const;
	
public:
	GestorDepartamentos(ListaDepartamentos* departamentos, ListaComprobantes* comprobantes,
						PersistenciaArchivos* persistencia, Validaciones* validador);
	~GestorDepartamentos();
	
	string registrarDepartamento(const string& codigo, const string& nombre);
	string actualizarDepartamento(const string& codigo, const string& nombre);
	string eliminarDepartamento(const string& codigo);
	
	string registrarPuesto(const string& codigoDepto, const string& codigoPuesto,
						   const string& nombre, double salarioBase);
	string actualizarPuesto(const string& codigoDepto, const string& codigoPuesto,
							const string& nombre, double salarioBase);
	string eliminarPuesto(const string& codigoDepto, const string& codigoPuesto);
	
	Departamento* buscarDepartamento(const string& codigo) const;
	Departamento* obtenerEn(int indice) const;
	int getCantidad() const;
};

#endif
