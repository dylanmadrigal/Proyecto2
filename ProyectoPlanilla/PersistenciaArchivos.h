#ifndef PERSISTENCIAARCHIVOS_H
#define PERSISTENCIAARCHIVOS_H

#include <string>
#include "ListaEmpleados.h"
#include "ListaDepartamentos.h"
#include "ListaComprobantes.h"

using namespace std;

class PersistenciaArchivos {
private:
	string rutaEmpleados;
	string rutaDepartamentos;
	string rutaPlanilla;
	
public:
	PersistenciaArchivos(const string& rutaEmpleados,
						 const string& rutaDepartamentos,
						 const string& rutaPlanilla);
	~PersistenciaArchivos();
	
	bool cargarDepartamentos(ListaDepartamentos& departamentos) const;
	bool guardarDepartamentos(const ListaDepartamentos& departamentos) const;
	
	bool cargarEmpleados(ListaEmpleados& empleados) const;
	bool guardarEmpleados(const ListaEmpleados& empleados) const;
	
	bool cargarPlanilla(ListaComprobantes& comprobantes,
						const ListaEmpleados& empleados,
						const ListaDepartamentos& departamentos) const;
	bool guardarPlanilla(const ListaComprobantes& comprobantes) const;
};

#endif
