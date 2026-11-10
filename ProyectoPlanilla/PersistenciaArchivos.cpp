#include "PersistenciaArchivos.h"
#include <fstream>
#include <iomanip>
#include "Medico.h"
#include "Enfermero.h"
#include "Administrativo.h"

PersistenciaArchivos::PersistenciaArchivos(const string& rutaEmpleados,
										   const string& rutaDepartamentos,
										   const string& rutaPlanilla) {
	this->rutaEmpleados = rutaEmpleados;
	this->rutaDepartamentos = rutaDepartamentos;
	this->rutaPlanilla = rutaPlanilla;
}

PersistenciaArchivos::~PersistenciaArchivos() {
}

// ---------------------------------------------------------------- DEPARTAMENTOS

bool PersistenciaArchivos::guardarDepartamentos(const ListaDepartamentos& departamentos) const {
	fstream archivo;
	archivo.open(rutaDepartamentos, ios::out);
	if (!archivo.is_open()) {
		return false;
	}
	archivo << fixed << setprecision(2);
	
	for (int i = 0; i < departamentos.getCantidad(); i++) {
		const Departamento* d = departamentos.obtenerEn(i);
		archivo << d->getCodigo() << '\n';
		archivo << d->getNombre() << '\n';
		archivo << d->getCantidadPuestos() << '\n';
		
		for (int j = 0; j < d->getCantidadPuestos(); j++) {
			const Puesto* p = d->obtenerPuestoEn(j);
			archivo << p->getCodigo() << '\n';
			archivo << p->getNombre() << '\n';
			archivo << p->getSalarioBase() << '\n';
		}
	}
	
	bool exito = !archivo.fail();
	archivo.close();
	return exito;
}

bool PersistenciaArchivos::cargarDepartamentos(ListaDepartamentos& departamentos) const {
	fstream archivo;
	archivo.open(rutaDepartamentos, ios::in);
	if (!archivo.is_open()) {
		return false;
	}
	
	string codigo;
	while (getline(archivo, codigo)) {
		if (codigo.empty()) {
			continue;
		}
		string nombre;
		int cantidadPuestos;
		getline(archivo, nombre);
		archivo >> cantidadPuestos;
		archivo.ignore(1000, '\n');
		
		Departamento* departamento = new Departamento(codigo, nombre);
		for (int i = 0; i < cantidadPuestos; i++) {
			string codigoPuesto;
			string nombrePuesto;
			double salario;
			getline(archivo, codigoPuesto);
			getline(archivo, nombrePuesto);
			archivo >> salario;
			archivo.ignore(1000, '\n');
			departamento->agregarPuesto(new Puesto(codigoPuesto, nombrePuesto, salario));
		}
		
		if (archivo.fail()) {
			delete departamento;
			archivo.close();
			return false;
		}
		departamentos.insertarAlFinal(departamento);
	}
	
	archivo.close();
	return true;
}

// ------------------------------------------------------------------- EMPLEADOS

bool PersistenciaArchivos::guardarEmpleados(const ListaEmpleados& empleados) const {
	fstream archivo;
	archivo.open(rutaEmpleados, ios::out);
	if (!archivo.is_open()) {
		return false;
	}
	archivo << fixed << setprecision(2);
	
	for (int i = 0; i < empleados.getCantidad(); i++) {
		const Empleado* e = empleados.obtenerEn(i);
		const Medico* medico = dynamic_cast<const Medico*>(e);
		const Enfermero* enfermero = dynamic_cast<const Enfermero*>(e);
		const Administrativo* administrativo = dynamic_cast<const Administrativo*>(e);
		
		if (medico != NULL) {
			archivo << "MEDICO" << '\n';
		} else if (enfermero != NULL) {
			archivo << "ENFERMERO" << '\n';
		} else if (administrativo != NULL) {
			archivo << "ADMINISTRATIVO" << '\n';
		} else {
			archivo.close();
			return false;
		}
		
		archivo << e->getCedula() << '\n';
		archivo << e->getNombre() << '\n';
		archivo << e->getSalarioBase() << '\n';
		archivo << e->getHorasExtra() << '\n';
		
		if (medico != NULL) {
			archivo << medico->getEspecialidad() << '\n';
			archivo << medico->getGuardias() << '\n';
		} else if (enfermero != NULL) {
			archivo << enfermero->getTurno() << '\n';
			archivo << enfermero->getHorasNocturnas() << '\n';
		}
	}
	
	bool exito = !archivo.fail();
	archivo.close();
	return exito;
}

bool PersistenciaArchivos::cargarEmpleados(ListaEmpleados& empleados) const {
	fstream archivo;
	archivo.open(rutaEmpleados, ios::in);
	if (!archivo.is_open()) {
		return false;
	}
	
	string tipo;
	while (getline(archivo, tipo)) {
		if (tipo.empty()) {
			continue;
		}
		string cedula;
		string nombre;
		double salarioBase;
		double horasExtra;
		getline(archivo, cedula);
		getline(archivo, nombre);
		archivo >> salarioBase;
		archivo >> horasExtra;
		archivo.ignore(1000, '\n');
		
		if (tipo == "MEDICO") {
			string especialidad;
			int guardias;
			getline(archivo, especialidad);
			archivo >> guardias;
			archivo.ignore(1000, '\n');
			if (archivo.fail()) {
				archivo.close();
				return false;
			}
			empleados.insertarAlFinal(new Medico(cedula, nombre, salarioBase, horasExtra,
												 especialidad, guardias));
		} else if (tipo == "ENFERMERO") {
			string turno;
			int horasNocturnas;
			getline(archivo, turno);
			archivo >> horasNocturnas;
			archivo.ignore(1000, '\n');
			if (archivo.fail()) {
				archivo.close();
				return false;
			}
			empleados.insertarAlFinal(new Enfermero(cedula, nombre, salarioBase, horasExtra,
													turno, horasNocturnas));
		} else if (tipo == "ADMINISTRATIVO") {
			if (archivo.fail()) {
				archivo.close();
				return false;
			}
			empleados.insertarAlFinal(new Administrativo(cedula, nombre, salarioBase, horasExtra));
		} else {
			archivo.close();
			return false;
		}
	}
	
	archivo.close();
	return true;
}

// -------------------------------------------------------------------- PLANILLA

bool PersistenciaArchivos::guardarPlanilla(const ListaComprobantes& comprobantes) const {
	fstream archivo;
	archivo.open(rutaPlanilla, ios::out);
	if (!archivo.is_open()) {
		return false;
	}
	archivo << fixed << setprecision(2);
	
	for (int i = 0; i < comprobantes.getCantidad(); i++) {
		const ComprobantePago* c = comprobantes.obtenerEn(i);
		archivo << c->getCodigo() << '\n';
		archivo << c->getFecha() << '\n';
		archivo << c->getSalarioBruto() << '\n';
		archivo << c->getDeducciones() << '\n';
		archivo << c->getSalarioNeto() << '\n';
		archivo << c->getEmpleado()->getCedula() << '\n';
		archivo << c->getDepartamento()->getCodigo() << '\n';
	}
	
	bool exito = !archivo.fail();
	archivo.close();
	return exito;
}

bool PersistenciaArchivos::cargarPlanilla(ListaComprobantes& comprobantes,
										  const ListaEmpleados& empleados,
										  const ListaDepartamentos& departamentos) const {
	fstream archivo;
	archivo.open(rutaPlanilla, ios::in);
	if (!archivo.is_open()) {
		return false;
	}
	
	string codigo;
	while (getline(archivo, codigo)) {
		if (codigo.empty()) {
			continue;
		}
		string fecha;
		double salarioBruto;
		double deducciones;
		double salarioNeto;
		string cedulaEmpleado;
		string codigoDepartamento;
		getline(archivo, fecha);
		archivo >> salarioBruto;
		archivo >> deducciones;
		archivo >> salarioNeto;
		archivo.ignore(1000, '\n');
		getline(archivo, cedulaEmpleado);
		getline(archivo, codigoDepartamento);
		
		if (archivo.fail()) {
			archivo.close();
			return false;
		}
		
		// Agregacion: el comprobante solo apunta a objetos que ya existen en las otras listas
		Empleado* empleado = empleados.buscarPorCedula(cedulaEmpleado);
		Departamento* departamento = departamentos.buscarPorCodigo(codigoDepartamento);
		if (empleado != NULL && departamento != NULL) {
			comprobantes.insertarAlFinal(new ComprobantePago(codigo, fecha, salarioBruto,
															 deducciones, salarioNeto,
															 empleado, departamento));
		}
	}
	
	archivo.close();
	return true;
}
