#include "GestorDepartamentos.h"

GestorDepartamentos::GestorDepartamentos(ListaDepartamentos* departamentos,
										 ListaComprobantes* comprobantes,
										 PersistenciaArchivos* persistencia,
										 Validaciones* validador)
	: departamentos(departamentos), comprobantes(comprobantes),
	persistencia(persistencia), validador(validador) {
}

GestorDepartamentos::~GestorDepartamentos() {
	// No borra nada: las listas no son suyas (asociacion).
}

string GestorDepartamentos::guardar() const {
	if (!persistencia->guardarDepartamentos(*departamentos)) {
		return "Error: no se pudo guardar en el archivo de departamentos.";
	}
	return "";
}

string GestorDepartamentos::registrarDepartamento(const string& codigo, const string& nombre) {
	if (!validador->esTextoValido(codigo)) {
		return "El codigo del departamento no puede estar vacio.";
	}
	if (!validador->esTextoValido(nombre)) {
		return "El nombre del departamento no puede estar vacio.";
	}
	if (departamentos->buscarPorCodigo(codigo) != NULL) {
		return "Ya existe un departamento con ese codigo.";
	}
	departamentos->insertarAlFinal(new Departamento(codigo, nombre));
	return guardar();
}

string GestorDepartamentos::actualizarDepartamento(const string& codigo, const string& nombre) {
	Departamento* d = departamentos->buscarPorCodigo(codigo);
	if (d == NULL) {
		return "No existe un departamento con ese codigo.";
	}
	if (!validador->esTextoValido(nombre)) {
		return "El nombre del departamento no puede estar vacio.";
	}
	d->setNombre(nombre);
	return guardar();
}

string GestorDepartamentos::eliminarDepartamento(const string& codigo) {
	if (departamentos->buscarPorCodigo(codigo) == NULL) {
		return "No existe un departamento con ese codigo.";
	}
	if (comprobantes->existenDeDepartamento(codigo)) {
		return "No se puede eliminar: el departamento tiene comprobantes de pago.";
	}
	departamentos->eliminarPorCodigo(codigo);
	return guardar();
}

string GestorDepartamentos::registrarPuesto(const string& codigoDepto, const string& codigoPuesto,
											const string& nombre, double salarioBase) {
	Departamento* d = departamentos->buscarPorCodigo(codigoDepto);
	if (d == NULL) {
		return "No existe un departamento con ese codigo.";
	}
	if (!validador->esTextoValido(codigoPuesto)) {
		return "El codigo del puesto no puede estar vacio.";
	}
	if (!validador->esTextoValido(nombre)) {
		return "El nombre del puesto no puede estar vacio.";
	}
	if (!validador->esMontoPositivo(salarioBase)) {
		return "El salario del puesto debe ser mayor que cero.";
	}
	if (d->buscarPuesto(codigoPuesto) != NULL) {
		return "Ya existe un puesto con ese codigo en el departamento.";
	}
	d->agregarPuesto(new Puesto(codigoPuesto, nombre, salarioBase));
	return guardar();
}

string GestorDepartamentos::actualizarPuesto(const string& codigoDepto, const string& codigoPuesto,
											 const string& nombre, double salarioBase) {
	Departamento* d = departamentos->buscarPorCodigo(codigoDepto);
	if (d == NULL) {
		return "No existe un departamento con ese codigo.";
	}
	Puesto* p = d->buscarPuesto(codigoPuesto);
	if (p == NULL) {
		return "No existe un puesto con ese codigo en el departamento.";
	}
	if (!validador->esTextoValido(nombre)) {
		return "El nombre del puesto no puede estar vacio.";
	}
	if (!validador->esMontoPositivo(salarioBase)) {
		return "El salario del puesto debe ser mayor que cero.";
	}
	p->setNombre(nombre);
	p->setSalarioBase(salarioBase);
	return guardar();
}

string GestorDepartamentos::eliminarPuesto(const string& codigoDepto, const string& codigoPuesto) {
	Departamento* d = departamentos->buscarPorCodigo(codigoDepto);
	if (d == NULL) {
		return "No existe un departamento con ese codigo.";
	}
	if (!d->eliminarPuesto(codigoPuesto)) {
		return "No existe un puesto con ese codigo en el departamento.";
	}
	return guardar();
}

Departamento* GestorDepartamentos::buscarDepartamento(const string& codigo) const {
	return departamentos->buscarPorCodigo(codigo);
}

Departamento* GestorDepartamentos::obtenerEn(int indice) const {
	return departamentos->obtenerEn(indice);
}

int GestorDepartamentos::getCantidad() const {
	return departamentos->getCantidad();
}
