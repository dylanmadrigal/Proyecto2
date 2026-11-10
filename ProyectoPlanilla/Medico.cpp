#include "Medico.h"

const double Medico::MONTO_POR_GUARDIA = 20000;

Medico::Medico(const string& cedula, const string& nombre,
			   double salarioBase, double horasExtra,
			   const string& especialidad, int guardias)
	: Empleado(cedula, nombre, salarioBase, horasExtra) {
	this->especialidad = especialidad;
	this->guardias = guardias;
}

Medico::~Medico() {
}

string Medico::getEspecialidad() const { return especialidad; }
int Medico::getGuardias() const { return guardias; }

void Medico::setEspecialidad(const string& especialidad) { this->especialidad = especialidad; }
void Medico::setGuardias(int guardias) { this->guardias = guardias; }

double Medico::calcularBonificacion() const {
	return guardias * MONTO_POR_GUARDIA;
}
