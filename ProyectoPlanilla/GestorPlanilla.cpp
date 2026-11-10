#include "GestorPlanilla.h"

GestorPlanilla::GestorPlanilla(ListaEmpleados* empleados, ListaDepartamentos* departamentos,
							   ListaComprobantes* comprobantes, CalculadoraPlanilla* calculadora,
							   PersistenciaArchivos* persistencia, Validaciones* validador)
	: empleados(empleados), departamentos(departamentos), comprobantes(comprobantes),
	calculadora(calculadora), persistencia(persistencia), validador(validador) {
}

GestorPlanilla::~GestorPlanilla() {
	// No borra nada: todo lo que usa es de otros (asociacion).
}

string GestorPlanilla::guardar() const {
	if (!persistencia->guardarPlanilla(*comprobantes)) {
		return "Error: no se pudo guardar en el archivo de planilla.";
	}
	return "";
}

string GestorPlanilla::generarComprobante(const string& codigo, const string& fecha,
										  const string& cedulaEmpleado,
										  const string& codigoDepartamento) {
	if (!validador->esTextoValido(codigo)) {
		return "El codigo del comprobante no puede estar vacio.";
	}
	if (comprobantes->buscarPorCodigo(codigo) != NULL) {
		return "Ya existe un comprobante con ese codigo.";
	}
	if (!validador->esFechaValida(fecha)) {
		return "La fecha no es valida. Use el formato AAAA-MM-DD, por ejemplo 2026-11-08.";
	}
	Empleado* empleado = empleados->buscarPorCedula(cedulaEmpleado);
	if (empleado == NULL) {
		return "No existe un empleado con esa cedula.";
	}
	Departamento* departamento = departamentos->buscarPorCodigo(codigoDepartamento);
	if (departamento == NULL) {
		return "No existe un departamento con ese codigo.";
	}
	
	double bruto = calculadora->calcularSalarioBruto(empleado);
	double deducciones = calculadora->calcularDeducciones(bruto);
	double neto = calculadora->calcularSalarioNeto(empleado);
	
	// El comprobante apunta al empleado y al departamento (agregacion), no los copia.
	comprobantes->insertarAlFinal(new ComprobantePago(codigo, fecha, bruto, deducciones,
													  neto, empleado, departamento));
	return guardar();
}

string GestorPlanilla::eliminarComprobante(const string& codigo) {
	if (!comprobantes->eliminarPorCodigo(codigo)) {
		return "No existe un comprobante con ese codigo.";
	}
	return guardar();
}

ComprobantePago* GestorPlanilla::buscarComprobante(const string& codigo) const {
	return comprobantes->buscarPorCodigo(codigo);
}

ComprobantePago* GestorPlanilla::obtenerEn(int indice) const {
	return comprobantes->obtenerEn(indice);
}

int GestorPlanilla::getCantidad() const {
	return comprobantes->getCantidad();
}
