#ifndef GESTORPLANILLA_H
#define GESTORPLANILLA_H

#include <string>
#include "ListaEmpleados.h"
#include "ListaDepartamentos.h"
#include "ListaComprobantes.h"
#include "CalculadoraPlanilla.h"
#include "PersistenciaArchivos.h"
#include "Validaciones.h"

using namespace std;

class GestorPlanilla {
private:
	ListaEmpleados* empleados;
	ListaDepartamentos* departamentos;
	ListaComprobantes* comprobantes;
	CalculadoraPlanilla* calculadora;
	PersistenciaArchivos* persistencia;
	Validaciones* validador;
	
	string guardar() const;
	
public:
	GestorPlanilla(ListaEmpleados* empleados, ListaDepartamentos* departamentos,
				   ListaComprobantes* comprobantes, CalculadoraPlanilla* calculadora,
				   PersistenciaArchivos* persistencia, Validaciones* validador);
	~GestorPlanilla();
	
	string generarComprobante(const string& codigo, const string& fecha,
							  const string& cedulaEmpleado, const string& codigoDepartamento);
	string eliminarComprobante(const string& codigo);
	
	ComprobantePago* buscarComprobante(const string& codigo) const;
	ComprobantePago* obtenerEn(int indice) const;
	int getCantidad() const;
};

#endif
