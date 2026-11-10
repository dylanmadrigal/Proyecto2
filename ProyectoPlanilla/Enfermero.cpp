#include "Enfermero.h"

const double Enfermero::MONTO_POR_HORA_NOCTURNA = 1500;

Enfermero::Enfermero(const string& cedula, const string& nombre,
					 double salarioBase, double horasExtra,
					 const string& turno, int horasNocturnas)
	: Empleado(cedula, nombre, salarioBase, horasExtra) {
	this->turno = turno;
	this->horasNocturnas = horasNocturnas;
}

Enfermero::~Enfermero() {
}

string Enfermero::getTurno() const { return turno; }
int Enfermero::getHorasNocturnas() const { return horasNocturnas; }

void Enfermero::setTurno(const string& turno) { this->turno = turno; }
void Enfermero::setHorasNocturnas(int horasNocturnas) { this->horasNocturnas = horasNocturnas; }

double Enfermero::calcularBonificacion() const {
	return horasNocturnas * MONTO_POR_HORA_NOCTURNA;
}
