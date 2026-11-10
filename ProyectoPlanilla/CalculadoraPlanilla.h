#ifndef CALCULADORAPLANILLA_H
#define CALCULADORAPLANILLA_H

#include "Empleado.h"

class CalculadoraPlanilla {
private:
	// Horas extra
	static const double HORAS_AL_MES;
	static const double FACTOR_HORA_EXTRA;
	
	// Cargas sociales del trabajador (CCSS y Banco Popular)
	static const double PORCENTAJE_SEM;
	static const double PORCENTAJE_IVM;
	static const double PORCENTAJE_BANCO_POPULAR;
	
	// Impuesto sobre el salario (tramos mensuales)
	static const double RENTA_LIMITE_EXENTO;
	static const double RENTA_LIMITE_TRAMO_1;
	static const double RENTA_LIMITE_TRAMO_2;
	static const double RENTA_LIMITE_TRAMO_3;
	static const double RENTA_TASA_1;
	static const double RENTA_TASA_2;
	static const double RENTA_TASA_3;
	static const double RENTA_TASA_4;
	
public:
	CalculadoraPlanilla();
	~CalculadoraPlanilla();
	
	double calcularPagoHorasExtra(const Empleado* empleado) const;
	double calcularSalarioBruto(const Empleado* empleado) const;
	double calcularCargasSociales(double salarioBruto) const;
	double calcularImpuestoRenta(double salarioBruto) const;
	double calcularDeducciones(double salarioBruto) const;
	double calcularSalarioNeto(const Empleado* empleado) const;
};

#endif
