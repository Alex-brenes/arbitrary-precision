//integer.h
//Autor: José Alexander Brenes Brenes
//Clase para enteros de precisión arbitraria o bignum
#ifndef INTEGER_H
#define INTEGER_H
#include <string>
#include <sstream>
#include "doublelinkedlist.h"
#include "array.h"
#define MAX_DIGITS 9
#define ZERO 0
#define ONE 1

class Integer {

private:
	NodoDoble<Array>** integer;
	void add_digits(int);
	int cantidadDigitos() const;
	NodoDoble<Array>** getInteger() const;
public:
	Integer();
	Integer(const Integer&);
	Integer(int);
	Integer(long);
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
	friend std::ostream& operator<<(std::ostream&, const Integer&);
};


#endif // !INTEGER_H