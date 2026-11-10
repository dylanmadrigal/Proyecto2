#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <string>

using namespace std;

class Empleado {
private:
	string cedula;
	string nombre;
	double salarioBase;
	double horasExtra;
	
public:
	Empleado(const string& cedula, const string& nombre,
			 double salarioBase, double horasExtra);
	virtual ~Empleado();
	
	string getCedula() const;
	string getNombre() const;
	double getSalarioBase() const;
	double getHorasExtra() const;
	
	void setNombre(const string& nombre);
	void setSalarioBase(double salarioBase);
	void setHorasExtra(double horasExtra);
	
	virtual double calcularBonificacion() const = 0;
};

#endif
