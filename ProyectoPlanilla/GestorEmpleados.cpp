#include "GestorEmpleados.h"
#include "Medico.h"
#include "Enfermero.h"
#include "Administrativo.h"

GestorEmpleados::GestorEmpleados(ListaEmpleados* empleados, ListaComprobantes* comprobantes,
								 PersistenciaArchivos* persistencia, Validaciones* validador) {
	this->empleados = empleados;
	this->comprobantes = comprobantes;
	this->persistencia = persistencia;
	this->validador = validador;
}

GestorEmpleados::~GestorEmpleados() {
	// Asociacion: el gestor solo USA estos objetos, no es su dueno.
	// Por eso aqui no se hace delete de ninguno.
}

string GestorEmpleados::guardar() const {
	if (!persistencia->guardarEmpleados(*empleados)) {
		return "Error: no se pudo guardar en el archivo de empleados.";
	}
	return "";
}

string GestorEmpleados::validarDatosBasicos(const string& nombre, double salarioBase,
											double horasExtra) const {
	if (!validador->esTextoValido(nombre)) {
		return "El nombre no puede estar vacio.";
	}
	if (!validador->esMontoPositivo(salarioBase)) {
		return "El salario base debe ser mayor que cero.";
	}
	if (!validador->esNoNegativo(horasExtra)) {
		return "Las horas extra no pueden ser negativas.";
	}
	return "";
}

string GestorEmpleados::validarNuevoEmpleado(const string& cedula, const string& nombre,
											 double salarioBase, double horasExtra) const {
	if (!validador->esCedulaValida(cedula)) {
		return "La cedula debe tener entre 9 y 12 digitos, sin guiones ni espacios.";
	}
	if (empleados->buscarPorCedula(cedula) != NULL) {
		return "Ya existe un empleado con esa cedula.";
	}
	return validarDatosBasicos(nombre, salarioBase, horasExtra);
}

string GestorEmpleados::registrarMedico(const string& cedula, const string& nombre,
										double salarioBase, double horasExtra,
										const string& especialidad, int guardias) {
	string error = validarNuevoEmpleado(cedula, nombre, salarioBase, horasExtra);
	if (error != "") {
		return error;
	}
	if (!validador->esTextoValido(especialidad)) {
		return "La especialidad no puede estar vacia.";
	}
	if (guardias < 0) {
		return "Las guardias no pueden ser negativas.";
	}
	empleados->insertarAlFinal(new Medico(cedula, nombre, salarioBase, horasExtra,
										  especialidad, guardias));
	return guardar();
}

string GestorEmpleados::registrarEnfermero(const string& cedula, const string& nombre,
										   double salarioBase, double horasExtra,
										   const string& turno, int horasNocturnas) {
	string error = validarNuevoEmpleado(cedula, nombre, salarioBase, horasExtra);
	if (error != "") {
		return error;
	}
	if (!validador->esTextoValido(turno)) {
		return "El turno no puede estar vacio.";
	}
	if (horasNocturnas < 0) {
		return "Las horas nocturnas no pueden ser negativas.";
	}
	empleados->insertarAlFinal(new Enfermero(cedula, nombre, salarioBase, horasExtra,
											 turno, horasNocturnas));
	return guardar();
}

string GestorEmpleados::registrarAdministrativo(const string& cedula, const string& nombre,
												double salarioBase, double horasExtra) {
	string error = validarNuevoEmpleado(cedula, nombre, salarioBase, horasExtra);
	if (error != "") {
		return error;
	}
	empleados->insertarAlFinal(new Administrativo(cedula, nombre, salarioBase, horasExtra));
	return guardar();
}

string GestorEmpleados::actualizarEmpleado(const string& cedula, const string& nombre,
										   double salarioBase, double horasExtra) {
	Empleado* empleado = empleados->buscarPorCedula(cedula);
	if (empleado == NULL) {
		return "No existe un empleado con esa cedula.";
	}
	string error = validarDatosBasicos(nombre, salarioBase, horasExtra);
	if (error != "") {
		return error;
	}
	empleado->setNombre(nombre);
	empleado->setSalarioBase(salarioBase);
	empleado->setHorasExtra(horasExtra);
	return guardar();
}

string GestorEmpleados::actualizarGuardias(const string& cedula, int guardias) {
	Empleado* empleado = empleados->buscarPorCedula(cedula);
	if (empleado == NULL) {
		return "No existe un empleado con esa cedula.";
	}
	Medico* medico = dynamic_cast<Medico*>(empleado);
	if (medico == NULL) {
		return "Ese empleado no es medico.";
	}
	if (guardias < 0) {
		return "Las guardias no pueden ser negativas.";
	}
	medico->setGuardias(guardias);
	return guardar();
}

string GestorEmpleados::actualizarHorasNocturnas(const string& cedula, int horasNocturnas) {
	Empleado* empleado = empleados->buscarPorCedula(cedula);
	if (empleado == NULL) {
		return "No existe un empleado con esa cedula.";
	}
	Enfermero* enfermero = dynamic_cast<Enfermero*>(empleado);
	if (enfermero == NULL) {
		return "Ese empleado no es enfermero.";
	}
	if (horasNocturnas < 0) {
		return "Las horas nocturnas no pueden ser negativas.";
	}
	enfermero->setHorasNocturnas(horasNocturnas);
	return guardar();
}

string GestorEmpleados::eliminarEmpleado(const string& cedula) {
	if (empleados->buscarPorCedula(cedula) == NULL) {
		return "No existe un empleado con esa cedula.";
	}
	// Agregacion: un comprobante apunta a este empleado, no se puede dejar un puntero colgando
	if (comprobantes->existenDeEmpleado(cedula)) {
		return "No se puede eliminar: el empleado tiene comprobantes de pago.";
	}
	empleados->eliminarPorCedula(cedula);
	return guardar();
}

Empleado* GestorEmpleados::buscarEmpleado(const string& cedula) const {
	return empleados->buscarPorCedula(cedula);
}

Empleado* GestorEmpleados::obtenerEn(int indice) const {
	return empleados->obtenerEn(indice);
}

int GestorEmpleados::getCantidad() const {
	return empleados->getCantidad();
}
