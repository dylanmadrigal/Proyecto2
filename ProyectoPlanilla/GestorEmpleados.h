#ifndef GESTOREMPLEADOS_H
#define GESTOREMPLEADOS_H

#include <string>
#include "ListaEmpleados.h"
#include "ListaComprobantes.h"
#include "PersistenciaArchivos.h"
#include "Validaciones.h"

using namespace std;

class GestorEmpleados {
private:
	ListaEmpleados* empleados;
	ListaComprobantes* comprobantes;
	PersistenciaArchivos* persistencia;
	Validaciones* validador;
	
	string guardar() const;
	string validarDatosBasicos(const string& nombre, double salarioBase, double horasExtra) const;
	string validarNuevoEmpleado(const string& cedula, const string& nombre,
								double salarioBase, double horasExtra) const;
	
public:
	GestorEmpleados(ListaEmpleados* empleados, ListaComprobantes* comprobantes,
					PersistenciaArchivos* persistencia, Validaciones* validador);
	~GestorEmpleados();
	
	string registrarMedico(const string& cedula, const string& nombre,
						   double salarioBase, double horasExtra,
						   const string& especialidad, int guardias);
	string registrarEnfermero(const string& cedula, const string& nombre,
							  double salarioBase, double horasExtra,
							  const string& turno, int horasNocturnas);
	string registrarAdministrativo(const string& cedula, const string& nombre,
								   double salarioBase, double horasExtra);
	
	string actualizarEmpleado(const string& cedula, const string& nombre,
							  double salarioBase, double horasExtra);
	string actualizarGuardias(const string& cedula, int guardias);
	string actualizarHorasNocturnas(const string& cedula, int horasNocturnas);
	string eliminarEmpleado(const string& cedula);
	
	Empleado* buscarEmpleado(const string& cedula) const;
	Empleado* obtenerEn(int indice) const;
	int getCantidad() const;
};

#endif
