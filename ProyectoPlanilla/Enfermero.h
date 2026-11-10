#ifndef ENFERMERO_H
#define ENFERMERO_H

#include "Empleado.h"

class Enfermero : public Empleado {
private:
	string turno;
	int horasNocturnas;
	static const double MONTO_POR_HORA_NOCTURNA;
	
public:
	Enfermero(const string& cedula, const string& nombre,
			  double salarioBase, double horasExtra,
			  const string& turno, int horasNocturnas);
	virtual ~Enfermero();
	
	string getTurno() const;
	int getHorasNocturnas() const;
	
	void setTurno(const string& turno);
	void setHorasNocturnas(int horasNocturnas);
	
	virtual double calcularBonificacion() const;
};

#endif
