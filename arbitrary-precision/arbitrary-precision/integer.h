//integer.h
//Autor: José Alexander Brenes Brenes
//Clase para enteros de precisión arbitraria o bignum
#ifndef INTEGER_H
#define INTEGER_H
#include <string>

#include "doublelinkedlist.h"
#include "array.h"

#define ZERO 0
#define ONE 1

class Integer {

private:
	NodoDoble<Array>** integer;
	void add_digits(int);
public:
	Integer();
	Integer(int);
	Integer(long);
	NodoDoble<Array>** getInteger() const;
	static Integer& parse(std::string);
	~Integer();
};

std::ostream& operator<<(std::ostream&, const Integer&);

#endif // !INTEGER_H