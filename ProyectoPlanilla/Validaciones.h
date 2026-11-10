#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

using namespace std;

class Validaciones {
public:
	Validaciones();
	~Validaciones();
	
	bool esCedulaValida(const string& cedula) const;
	bool esTextoValido(const string& texto) const;
	bool esMontoPositivo(double monto) const;
	bool esNoNegativo(double valor) const;
	bool esFechaValida(const string& fecha) const;
};

#endif
