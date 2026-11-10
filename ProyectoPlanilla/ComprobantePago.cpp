#include "ComprobantePago.h"

ComprobantePago::ComprobantePago(const string& codigo, const string& fecha,
								 double salarioBruto, double deducciones, double salarioNeto,
								 Empleado* empleado, Departamento* departamento) {
	this->codigo = codigo;
	this->fecha = fecha;
	this->salarioBruto = salarioBruto;
	this->deducciones = deducciones;
	this->salarioNeto = salarioNeto;
	this->empleado = empleado;
	this->departamento = departamento;
}

ComprobantePago::~ComprobantePago() {
	// Agregacion: el empleado y el departamento NO se borran aqui,
	// porque existen de forma independiente en sus propias listas.
}

string ComprobantePago::getCodigo() const { return codigo; }
string ComprobantePago::getFecha() const { return fecha; }
double ComprobantePago::getSalarioBruto() const { return salarioBruto; }
double ComprobantePago::getDeducciones() const { return deducciones; }
double ComprobantePago::getSalarioNeto() const { return salarioNeto; }
Empleado* ComprobantePago::getEmpleado() const { return empleado; }
Departamento* ComprobantePago::getDepartamento() const { return departamento; }
