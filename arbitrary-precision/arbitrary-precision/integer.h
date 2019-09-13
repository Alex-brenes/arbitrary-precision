//integer.h
//Autor: José Alexander Brenes Brenes
//Clase para enteros de precisión arbitraria o bignum
#ifndef INTEGER_H
#define INTEGER_H
#include <string>

#include "listasimple.h"
#include "array.h"

#define ZERO 0
#define ONE 1

class Integer {

private:
	NodoSimple<Array>** integer;
	void add_digits(int);
	int cantidadDigitos() const;
public:
	Integer();
	Integer(int);
	Integer(long);
	NodoSimple<Array>** getInteger() const;
	static Integer& parse(std::string);
	Integer& operator=(const Integer&);
	Integer& operator+(const Integer&);
	Integer& operator-(const Integer&);
	Integer& operator*(const Integer&);
	Integer& operator/(const Integer&);
	bool operator<(const Integer&);
	bool operator>(const Integer&);
	bool operator<=(const Integer&);
	bool operator>=(const Integer&);
	bool operator==(const Integer&);
	~Integer();
};

std::ostream& operator<<(std::ostream&, const Integer&);

#endif // !INTEGER_H