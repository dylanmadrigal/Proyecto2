#include "CalculadoraPlanilla.h"

const double CalculadoraPlanilla::HORAS_AL_MES = 240;
const double CalculadoraPlanilla::FACTOR_HORA_EXTRA = 1.5;

const double CalculadoraPlanilla::PORCENTAJE_SEM = 0.055;
const double CalculadoraPlanilla::PORCENTAJE_IVM = 0.0433;
const double CalculadoraPlanilla::PORCENTAJE_BANCO_POPULAR = 0.01;

const double CalculadoraPlanilla::RENTA_LIMITE_EXENTO = 918000;
const double CalculadoraPlanilla::RENTA_LIMITE_TRAMO_1 = 1347000;
const double CalculadoraPlanilla::RENTA_LIMITE_TRAMO_2 = 2364000;
const double CalculadoraPlanilla::RENTA_LIMITE_TRAMO_3 = 4727000;
const double CalculadoraPlanilla::RENTA_TASA_1 = 0.10;
const double CalculadoraPlanilla::RENTA_TASA_2 = 0.15;
const double CalculadoraPlanilla::RENTA_TASA_3 = 0.20;
const double CalculadoraPlanilla::RENTA_TASA_4 = 0.25;

CalculadoraPlanilla::CalculadoraPlanilla() {
}

CalculadoraPlanilla::~CalculadoraPlanilla() {
}

double CalculadoraPlanilla::calcularPagoHorasExtra(const Empleado* empleado) const {
	double valorHora = empleado->getSalarioBase() / HORAS_AL_MES;
	return empleado->getHorasExtra() * valorHora * FACTOR_HORA_EXTRA;
}

double CalculadoraPlanilla::calcularSalarioBruto(const Empleado* empleado) const {
	// calcularBonificacion() es polimorfico: cada tipo de empleado responde a su manera
	return empleado->getSalarioBase()
		+ calcularPagoHorasExtra(empleado)
		+ empleado->calcularBonificacion();
}

double CalculadoraPlanilla::calcularCargasSociales(double salarioBruto) const {
	double porcentajeTotal = PORCENTAJE_SEM + PORCENTAJE_IVM + PORCENTAJE_BANCO_POPULAR;
	return salarioBruto * porcentajeTotal;
}

double CalculadoraPlanilla::calcularImpuestoRenta(double salarioBruto) const {
	double impuesto = 0;
	
	if (salarioBruto > RENTA_LIMITE_EXENTO) {
		double tope = salarioBruto < RENTA_LIMITE_TRAMO_1 ? salarioBruto : RENTA_LIMITE_TRAMO_1;
		impuesto += (tope - RENTA_LIMITE_EXENTO) * RENTA_TASA_1;
	}
	if (salarioBruto > RENTA_LIMITE_TRAMO_1) {
		double tope = salarioBruto < RENTA_LIMITE_TRAMO_2 ? salarioBruto : RENTA_LIMITE_TRAMO_2;
		impuesto += (tope - RENTA_LIMITE_TRAMO_1) * RENTA_TASA_2;
	}
	if (salarioBruto > RENTA_LIMITE_TRAMO_2) {
		double tope = salarioBruto < RENTA_LIMITE_TRAMO_3 ? salarioBruto : RENTA_LIMITE_TRAMO_3;
		impuesto += (tope - RENTA_LIMITE_TRAMO_2) * RENTA_TASA_3;
	}
	if (salarioBruto > RENTA_LIMITE_TRAMO_3) {
		impuesto += (salarioBruto - RENTA_LIMITE_TRAMO_3) * RENTA_TASA_4;
	}
	
	return impuesto;
}

double CalculadoraPlanilla::calcularDeducciones(double salarioBruto) const {
	return calcularCargasSociales(salarioBruto) + calcularImpuestoRenta(salarioBruto);
}

double CalculadoraPlanilla::calcularSalarioNeto(const Empleado* empleado) const {
	double bruto = calcularSalarioBruto(empleado);
	return bruto - calcularDeducciones(bruto);
}
