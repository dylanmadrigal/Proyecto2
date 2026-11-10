#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "GestorEmpleados.h"
#include "GestorDepartamentos.h"
#include "GestorPlanilla.h"
#include "Medico.h"
#include "Enfermero.h"

using namespace std;

// ---------- Utilidades de consola (solo este archivo usa cin y cout) ----------

void limpiarPantalla() {
	system("cls");
}

void pausa() {
	cout << endl << "Presione Enter para continuar...";
	string basura;
	getline(cin, basura);
}

void salirSiSeCerroEntrada() {
	if (cin.eof()) {
		cout << endl;
		exit(0);
	}
}

string leerTexto(const string& mensaje) {
	string texto;
	cout << mensaje;
	getline(cin, texto);
	salirSiSeCerroEntrada();
	return texto;
}

int leerEntero(const string& mensaje) {
	int valor;
	cout << mensaje;
	while (!(cin >> valor)) {
		salirSiSeCerroEntrada();
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Valor no valido. Escriba un numero entero: ";
	}
	cin.ignore(1000, '\n');
	return valor;
}

double leerDecimal(const string& mensaje) {
	double valor;
	cout << mensaje;
	while (!(cin >> valor)) {
		salirSiSeCerroEntrada();
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Valor no valido. Escriba un numero: ";
	}
	cin.ignore(1000, '\n');
	return valor;
}

void mostrarResultado(const string& resultado, const string& mensajeExito) {
	if (resultado == "") {
		cout << endl << mensajeExito << endl;
	} else {
		cout << endl << resultado << endl;
	}
}

void titulo(const string& texto) {
	limpiarPantalla();
	cout << "==============================================" << endl;
	cout << "  " << texto << endl;
	cout << "==============================================" << endl;
}

// ---------- Mostrar datos ----------

void mostrarEmpleado(const Empleado* e) {
	cout << "Cedula: " << e->getCedula() << endl;
	cout << "Nombre: " << e->getNombre() << endl;
	cout << "Salario base: " << e->getSalarioBase() << endl;
	cout << "Horas extra: " << e->getHorasExtra() << endl;
	
	const Medico* m = dynamic_cast<const Medico*>(e);
	const Enfermero* en = dynamic_cast<const Enfermero*>(e);
	if (m != NULL) {
		cout << "Tipo: Medico" << endl;
		cout << "Especialidad: " << m->getEspecialidad() << endl;
		cout << "Guardias: " << m->getGuardias() << endl;
	} else if (en != NULL) {
		cout << "Tipo: Enfermero" << endl;
		cout << "Turno: " << en->getTurno() << endl;
		cout << "Horas nocturnas: " << en->getHorasNocturnas() << endl;
	} else {
		cout << "Tipo: Administrativo" << endl;
	}
}

void mostrarDepartamento(const Departamento* d) {
	cout << "Codigo: " << d->getCodigo() << endl;
	cout << "Nombre: " << d->getNombre() << endl;
	cout << "Puestos: " << d->getCantidadPuestos() << endl;
	for (int i = 0; i < d->getCantidadPuestos(); i++) {
		Puesto* p = d->obtenerPuestoEn(i);
		cout << "   - " << p->getCodigo() << " | " << p->getNombre()
			<< " | Salario: " << p->getSalarioBase() << endl;
	}
}

void mostrarComprobante(const ComprobantePago* c) {
	cout << "Comprobante: " << c->getCodigo() << endl;
	cout << "Fecha: " << c->getFecha() << endl;
	cout << "Empleado: " << c->getEmpleado()->getNombre()
		<< " (" << c->getEmpleado()->getCedula() << ")" << endl;
	cout << "Departamento: " << c->getDepartamento()->getNombre() << endl;
	cout << "Salario bruto: " << c->getSalarioBruto() << endl;
	cout << "Deducciones: " << c->getDeducciones() << endl;
	cout << "Salario neto: " << c->getSalarioNeto() << endl;
}

// ---------- Menu de empleados ----------

void registrarEmpleado(GestorEmpleados& gestor) {
	titulo("REGISTRAR EMPLEADO");
	cout << "1. Medico" << endl;
	cout << "2. Enfermero" << endl;
	cout << "3. Administrativo" << endl;
	cout << "4. Cancelar" << endl;
	int tipo = leerEntero("Tipo de empleado: ");
	if (tipo != 1 && tipo != 2 && tipo != 3) {
		return;
	}
	
	cout << endl;
	string cedula = leerTexto("Cedula (solo numeros): ");
	string nombre = leerTexto("Nombre completo: ");
	double salario = leerDecimal("Salario base mensual: ");
	double horasExtra = leerDecimal("Horas extra del mes: ");
	
	string resultado;
	if (tipo == 1) {
		string especialidad = leerTexto("Especialidad: ");
		int guardias = leerEntero("Cantidad de guardias: ");
		resultado = gestor.registrarMedico(cedula, nombre, salario, horasExtra, especialidad, guardias);
	} else if (tipo == 2) {
		string turno = leerTexto("Turno (Diurno, Mixto o Nocturno): ");
		int horasNocturnas = leerEntero("Horas nocturnas del mes: ");
		resultado = gestor.registrarEnfermero(cedula, nombre, salario, horasExtra, turno, horasNocturnas);
	} else {
		resultado = gestor.registrarAdministrativo(cedula, nombre, salario, horasExtra);
	}
	mostrarResultado(resultado, "Empleado registrado correctamente.");
	pausa();
}

void listarEmpleados(const GestorEmpleados& gestor) {
	titulo("LISTA DE EMPLEADOS");
	if (gestor.getCantidad() == 0) {
		cout << "No hay empleados registrados." << endl;
	}
	for (int i = 0; i < gestor.getCantidad(); i++) {
		cout << "--- Empleado " << (i + 1) << " ---" << endl;
		mostrarEmpleado(gestor.obtenerEn(i));
		cout << endl;
	}
	pausa();
}

void buscarEmpleado(const GestorEmpleados& gestor) {
	titulo("BUSCAR EMPLEADO");
	string cedula = leerTexto("Cedula: ");
	Empleado* e = gestor.buscarEmpleado(cedula);
	cout << endl;
	if (e == NULL) {
		cout << "No existe un empleado con esa cedula." << endl;
	} else {
		mostrarEmpleado(e);
	}
	pausa();
}

void actualizarEmpleado(GestorEmpleados& gestor) {
	titulo("ACTUALIZAR EMPLEADO");
	string cedula = leerTexto("Cedula del empleado: ");
	Empleado* e = gestor.buscarEmpleado(cedula);
	if (e == NULL) {
		cout << endl << "No existe un empleado con esa cedula." << endl;
		pausa();
		return;
	}
	cout << endl;
	mostrarEmpleado(e);
	cout << endl << "Escriba los datos nuevos:" << endl;
	string nombre = leerTexto("Nombre completo: ");
	double salario = leerDecimal("Salario base mensual: ");
	double horasExtra = leerDecimal("Horas extra del mes: ");
	string resultado = gestor.actualizarEmpleado(cedula, nombre, salario, horasExtra);
	
	if (resultado == "") {
		if (dynamic_cast<Medico*>(e) != NULL) {
			int guardias = leerEntero("Cantidad de guardias: ");
			resultado = gestor.actualizarGuardias(cedula, guardias);
		} else if (dynamic_cast<Enfermero*>(e) != NULL) {
			int horasNocturnas = leerEntero("Horas nocturnas del mes: ");
			resultado = gestor.actualizarHorasNocturnas(cedula, horasNocturnas);
		}
	}
	mostrarResultado(resultado, "Empleado actualizado correctamente.");
	pausa();
}

void eliminarEmpleado(GestorEmpleados& gestor) {
	titulo("ELIMINAR EMPLEADO");
	string cedula = leerTexto("Cedula del empleado: ");
	Empleado* e = gestor.buscarEmpleado(cedula);
	if (e == NULL) {
		cout << endl << "No existe un empleado con esa cedula." << endl;
		pausa();
		return;
	}
	cout << endl;
	mostrarEmpleado(e);
	string confirmacion = leerTexto("\nEscriba S para confirmar la eliminacion: ");
	if (confirmacion == "S" || confirmacion == "s") {
		mostrarResultado(gestor.eliminarEmpleado(cedula), "Empleado eliminado correctamente.");
	} else {
		cout << endl << "Eliminacion cancelada." << endl;
	}
	pausa();
}

void menuEmpleados(GestorEmpleados& gestor) {
	int opcion = 0;
	while (opcion != 6) {
		titulo("MENU DE EMPLEADOS");
		cout << "1. Registrar empleado" << endl;
		cout << "2. Listar empleados" << endl;
		cout << "3. Buscar empleado" << endl;
		cout << "4. Actualizar empleado" << endl;
		cout << "5. Eliminar empleado" << endl;
		cout << "6. Volver" << endl;
		opcion = leerEntero("Opcion: ");
		if (opcion == 1) registrarEmpleado(gestor);
		else if (opcion == 2) listarEmpleados(gestor);
		else if (opcion == 3) buscarEmpleado(gestor);
		else if (opcion == 4) actualizarEmpleado(gestor);
		else if (opcion == 5) eliminarEmpleado(gestor);
		else if (opcion != 6) { cout << "Opcion no valida." << endl; pausa(); }
	}
}

// ---------- Menu de departamentos ----------

void registrarDepartamento(GestorDepartamentos& gestor) {
	titulo("REGISTRAR DEPARTAMENTO");
	string codigo = leerTexto("Codigo (ejemplo D01): ");
	string nombre = leerTexto("Nombre: ");
	mostrarResultado(gestor.registrarDepartamento(codigo, nombre), "Departamento registrado correctamente.");
	pausa();
}

void listarDepartamentos(const GestorDepartamentos& gestor) {
	titulo("LISTA DE DEPARTAMENTOS");
	if (gestor.getCantidad() == 0) {
		cout << "No hay departamentos registrados." << endl;
	}
	for (int i = 0; i < gestor.getCantidad(); i++) {
		cout << "--- Departamento " << (i + 1) << " ---" << endl;
		mostrarDepartamento(gestor.obtenerEn(i));
		cout << endl;
	}
	pausa();
}

void actualizarDepartamento(GestorDepartamentos& gestor) {
	titulo("ACTUALIZAR DEPARTAMENTO");
	string codigo = leerTexto("Codigo del departamento: ");
	string nombre = leerTexto("Nombre nuevo: ");
	mostrarResultado(gestor.actualizarDepartamento(codigo, nombre), "Departamento actualizado correctamente.");
	pausa();
}

void eliminarDepartamento(GestorDepartamentos& gestor) {
	titulo("ELIMINAR DEPARTAMENTO");
	string codigo = leerTexto("Codigo del departamento: ");
	Departamento* d = gestor.buscarDepartamento(codigo);
	if (d == NULL) {
		cout << endl << "No existe un departamento con ese codigo." << endl;
		pausa();
		return;
	}
	cout << endl;
	mostrarDepartamento(d);
	cout << "\nSe eliminaran tambien sus puestos." << endl;
	string confirmacion = leerTexto("Escriba S para confirmar la eliminacion: ");
	if (confirmacion == "S" || confirmacion == "s") {
		mostrarResultado(gestor.eliminarDepartamento(codigo), "Departamento eliminado correctamente.");
	} else {
		cout << endl << "Eliminacion cancelada." << endl;
	}
	pausa();
}

void registrarPuesto(GestorDepartamentos& gestor) {
	titulo("REGISTRAR PUESTO");
	string codigoDepto = leerTexto("Codigo del departamento: ");
	string codigoPuesto = leerTexto("Codigo del puesto (ejemplo P01): ");
	string nombre = leerTexto("Nombre del puesto: ");
	double salario = leerDecimal("Salario base del puesto: ");
	mostrarResultado(gestor.registrarPuesto(codigoDepto, codigoPuesto, nombre, salario), "Puesto registrado correctamente.");
	pausa();
}

void actualizarPuesto(GestorDepartamentos& gestor) {
	titulo("ACTUALIZAR PUESTO");
	string codigoDepto = leerTexto("Codigo del departamento: ");
	string codigoPuesto = leerTexto("Codigo del puesto: ");
	string nombre = leerTexto("Nombre nuevo: ");
	double salario = leerDecimal("Salario base nuevo: ");
	mostrarResultado(gestor.actualizarPuesto(codigoDepto, codigoPuesto, nombre, salario), "Puesto actualizado correctamente.");
	pausa();
}

void eliminarPuesto(GestorDepartamentos& gestor) {
	titulo("ELIMINAR PUESTO");
	string codigoDepto = leerTexto("Codigo del departamento: ");
	string codigoPuesto = leerTexto("Codigo del puesto: ");
	mostrarResultado(gestor.eliminarPuesto(codigoDepto, codigoPuesto), "Puesto eliminado correctamente.");
	pausa();
}

void menuDepartamentos(GestorDepartamentos& gestor) {
	int opcion = 0;
	while (opcion != 8) {
		titulo("MENU DE DEPARTAMENTOS");
		cout << "1. Registrar departamento" << endl;
		cout << "2. Listar departamentos (con sus puestos)" << endl;
		cout << "3. Actualizar departamento" << endl;
		cout << "4. Eliminar departamento" << endl;
		cout << "5. Registrar puesto" << endl;
		cout << "6. Actualizar puesto" << endl;
		cout << "7. Eliminar puesto" << endl;
		cout << "8. Volver" << endl;
		opcion = leerEntero("Opcion: ");
		if (opcion == 1) registrarDepartamento(gestor);
		else if (opcion == 2) listarDepartamentos(gestor);
		else if (opcion == 3) actualizarDepartamento(gestor);
		else if (opcion == 4) eliminarDepartamento(gestor);
		else if (opcion == 5) registrarPuesto(gestor);
		else if (opcion == 6) actualizarPuesto(gestor);
		else if (opcion == 7) eliminarPuesto(gestor);
		else if (opcion != 8) { cout << "Opcion no valida." << endl; pausa(); }
	}
}

// ---------- Menu de planilla ----------

void generarComprobante(GestorPlanilla& gestor) {
	titulo("GENERAR COMPROBANTE DE PAGO");
	string codigo = leerTexto("Codigo del comprobante (ejemplo C001): ");
	string fecha = leerTexto("Fecha (AAAA-MM-DD): ");
	string cedula = leerTexto("Cedula del empleado: ");
	string codigoDepto = leerTexto("Codigo del departamento: ");
	string resultado = gestor.generarComprobante(codigo, fecha, cedula, codigoDepto);
	mostrarResultado(resultado, "Comprobante generado correctamente.");
	if (resultado == "") {
		cout << endl;
		mostrarComprobante(gestor.buscarComprobante(codigo));
	}
	pausa();
}

void listarComprobantes(const GestorPlanilla& gestor) {
	titulo("LISTA DE COMPROBANTES");
	if (gestor.getCantidad() == 0) {
		cout << "No hay comprobantes registrados." << endl;
	}
	for (int i = 0; i < gestor.getCantidad(); i++) {
		cout << "--- Comprobante " << (i + 1) << " ---" << endl;
		mostrarComprobante(gestor.obtenerEn(i));
		cout << endl;
	}
	pausa();
}

void buscarComprobante(const GestorPlanilla& gestor) {
	titulo("BUSCAR COMPROBANTE");
	string codigo = leerTexto("Codigo del comprobante: ");
	ComprobantePago* c = gestor.buscarComprobante(codigo);
	cout << endl;
	if (c == NULL) {
		cout << "No existe un comprobante con ese codigo." << endl;
	} else {
		mostrarComprobante(c);
	}
	pausa();
}

void eliminarComprobante(GestorPlanilla& gestor) {
	titulo("ELIMINAR COMPROBANTE");
	string codigo = leerTexto("Codigo del comprobante: ");
	mostrarResultado(gestor.eliminarComprobante(codigo), "Comprobante eliminado correctamente.");
	pausa();
}

void menuPlanilla(GestorPlanilla& gestor) {
	int opcion = 0;
	while (opcion != 5) {
		titulo("MENU DE PLANILLA");
		cout << "1. Generar comprobante de pago" << endl;
		cout << "2. Listar comprobantes" << endl;
		cout << "3. Buscar comprobante" << endl;
		cout << "4. Eliminar comprobante" << endl;
		cout << "5. Volver" << endl;
		opcion = leerEntero("Opcion: ");
		if (opcion == 1) generarComprobante(gestor);
		else if (opcion == 2) listarComprobantes(gestor);
		else if (opcion == 3) buscarComprobante(gestor);
		else if (opcion == 4) eliminarComprobante(gestor);
		else if (opcion != 5) { cout << "Opcion no valida." << endl; pausa(); }
	}
}

// ---------- Programa principal ----------

int main() {
	cout << fixed << setprecision(2);
	
	PersistenciaArchivos persistencia("data/empleados.txt", "data/departamentos.txt", "data/planilla.txt");
	Validaciones validador;
	CalculadoraPlanilla calculadora;
	ListaEmpleados empleados;
	ListaDepartamentos departamentos;
	ListaComprobantes comprobantes;
	
	// Carga automatica al iniciar. El orden importa: la planilla apunta a empleados y departamentos.
	bool okDepartamentos = persistencia.cargarDepartamentos(departamentos);
	bool okEmpleados = persistencia.cargarEmpleados(empleados);
	bool okPlanilla = persistencia.cargarPlanilla(comprobantes, empleados, departamentos);
	
	GestorEmpleados gestorEmpleados(&empleados, &comprobantes, &persistencia, &validador);
	GestorDepartamentos gestorDepartamentos(&departamentos, &comprobantes, &persistencia, &validador);
	GestorPlanilla gestorPlanilla(&empleados, &departamentos, &comprobantes, &calculadora,
								  &persistencia, &validador);
	
	if (!okDepartamentos || !okEmpleados || !okPlanilla) {
		cout << "Aviso: algun archivo de datos no se pudo leer (o no existe todavia)." << endl;
		cout << "El sistema inicia con esos datos vacios; se crearan al guardar." << endl;
		pausa();
	}
	
	int opcion = 0;
	while (opcion != 4) {
		titulo("SISTEMA DE PLANILLA HOSPITALARIA");
		cout << "1. Empleados" << endl;
		cout << "2. Departamentos y puestos" << endl;
		cout << "3. Planilla y comprobantes" << endl;
		cout << "4. Salir" << endl;
		opcion = leerEntero("Opcion: ");
		if (opcion == 1) menuEmpleados(gestorEmpleados);
		else if (opcion == 2) menuDepartamentos(gestorDepartamentos);
		else if (opcion == 3) menuPlanilla(gestorPlanilla);
		else if (opcion != 4) { cout << "Opcion no valida." << endl; pausa(); }
	}
	
	cout << endl << "Datos guardados. Hasta luego." << endl;
	return 0;
}
