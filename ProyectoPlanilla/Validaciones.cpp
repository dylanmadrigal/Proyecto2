#include "Validaciones.h"

Validaciones::Validaciones() {
}

Validaciones::~Validaciones() {
}

bool Validaciones::esCedulaValida(const string& cedula) const {
	if (cedula.length() < 9 || cedula.length() > 12) {
		return false;
	}
	for (unsigned int i = 0; i < cedula.length(); i++) {
		if (cedula[i] < '0' || cedula[i] > '9') {
			return false;
		}
	}
	return true;
}

bool Validaciones::esTextoValido(const string& texto) const {
	for (unsigned int i = 0; i < texto.length(); i++) {
		if (texto[i] != ' ') {
			return true;
		}
	}
	return false;
}

bool Validaciones::esMontoPositivo(double monto) const {
	return monto > 0;
}

bool Validaciones::esNoNegativo(double valor) const {
	return valor >= 0;
}

bool Validaciones::esFechaValida(const string& fecha) const {
	// Formato exacto: AAAA-MM-DD (10 caracteres)
	if (fecha.length() != 10 || fecha[4] != '-' || fecha[7] != '-') {
		return false;
	}
	for (int i = 0; i < 10; i++) {
		if (i != 4 && i != 7 && (fecha[i] < '0' || fecha[i] > '9')) {
			return false;
		}
	}
	int anio = (fecha[0] - '0') * 1000 + (fecha[1] - '0') * 100 +
		(fecha[2] - '0') * 10 + (fecha[3] - '0');
	int mes = (fecha[5] - '0') * 10 + (fecha[6] - '0');
	int dia = (fecha[8] - '0') * 10 + (fecha[9] - '0');
	
	if (anio < 2000 || mes < 1 || mes > 12 || dia < 1) {
		return false;
	}
	int diasDelMes = 31;
	if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
		diasDelMes = 30;
	} else if (mes == 2) {
		bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
		diasDelMes = bisiesto ? 29 : 28;
	}
	return dia <= diasDelMes;
}
