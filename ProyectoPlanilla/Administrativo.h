#ifndef ADMINISTRATIVO_H
#define ADMINISTRATIVO_H

#include "Empleado.h"

class Administrativo : public Empleado {
public:
	Administrativo(const string& cedula, const string& nombre,
				   double salarioBase, double horasExtra);
	virtual ~Administrativo();
	
	virtual double calcularBonificacion() const;
};

#endif
