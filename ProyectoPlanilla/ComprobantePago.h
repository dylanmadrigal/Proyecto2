#ifndef COMPROBANTEPAGO_H
#define COMPROBANTEPAGO_H

#include <string>
#include "Empleado.h"
#include "Departamento.h"

using namespace std;

class ComprobantePago {
private:
	string codigo;
	string fecha;
	double salarioBruto;
	double deducciones;
	double salarioNeto;
	Empleado* empleado;
	Departamento* departamento;
	
public:
	ComprobantePago(const string& codigo, const string& fecha,
					double salarioBruto, double deducciones, double salarioNeto,
					Empleado* empleado, Departamento* departamento);
	~ComprobantePago();
	
	string getCodigo() const;
	string getFecha() const;
	double getSalarioBruto() const;
	double getDeducciones() const;
	double getSalarioNeto() const;
	Empleado* getEmpleado() const;
	Departamento* getDepartamento() const;
};

#endif
