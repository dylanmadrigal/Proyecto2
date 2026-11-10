#ifndef PUESTO_H
#define PUESTO_H

#include <string>

using namespace std;

class Puesto {
private:
	string codigo;
	string nombre;
	double salarioBase;
	
public:
	Puesto(const string& codigo, const string& nombre, double salarioBase);
	~Puesto();
	
	string getCodigo() const;
	string getNombre() const;
	double getSalarioBase() const;
	
	void setNombre(const string& nombre);
	void setSalarioBase(double salarioBase);
};

#endif
