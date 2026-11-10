#include "Administrativo.h"

Administrativo::Administrativo(const string& cedula, const string& nombre,
							   double salarioBase, double horasExtra)
	: Empleado(cedula, nombre, salarioBase, horasExtra) {
}

Administrativo::~Administrativo() {
}

double Administrativo::calcularBonificacion() const {
	return 0;
}
