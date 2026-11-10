#ifndef MEDICO_H
#define MEDICO_H

#include "Empleado.h"

class Medico : public Empleado {
private:
	string especialidad;
	int guardias;
	static const double MONTO_POR_GUARDIA;
	
public:
	Medico(const string& cedula, const string& nombre,
		   double salarioBase, double horasExtra,
		   const string& especialidad, int guardias);
	virtual ~Medico();
	
	string getEspecialidad() const;
	int getGuardias() const;
	
	void setEspecialidad(const string& especialidad);
	void setGuardias(int guardias);
	
	virtual double calcularBonificacion() const;
};

#endif
