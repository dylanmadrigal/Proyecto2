#ifndef DEPARTAMENTO_H
#define DEPARTAMENTO_H

#include <string>
#include "ListaPuestos.h"

using namespace std;

class Departamento {
private:
	string codigo;
	string nombre;
	ListaPuestos puestos;
	
public:
	Departamento(const string& codigo, const string& nombre);
	~Departamento();
	
	string getCodigo() const;
	string getNombre() const;
	void setNombre(const string& nombre);
	
	void agregarPuesto(Puesto* puesto);
	Puesto* buscarPuesto(const string& codigo) const;
	bool eliminarPuesto(const string& codigo);
	Puesto* obtenerPuestoEn(int indice) const;
	int getCantidadPuestos() const;
};

#endif
