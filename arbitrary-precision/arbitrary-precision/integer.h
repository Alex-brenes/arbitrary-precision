//integer.h
//Autor: José Alexander Brenes Brenes
//Clase para enteros de precisión arbitraria o bignum
#ifndef INTEGER_H
#define INTEGER_H
#include <string>
#include <sstream>
#include <math.h>
#include "doublelinkedlist.h"
#include "array.h"
#define MAX_DIGITS 9
//#define ZERO 0
//#define ONE 1

class Integer {

private:

	NodoDoble<Array>** integer;
	void add_digits(int);
	int cantidadDigitos() const;
	NodoDoble<Array>** getInteger() const;
	void add_one_by_one(int);
	void add_one_digit(int);
	void add_shift(int);
	void clear_integer();
	bool operator==(const Integer&) const;
	bool is_positive() const;
	bool is_negative() const;
public:
	static const Integer ONE;
	static const Integer ZERO;
	Integer();
	Integer(const Integer&);
	Integer(int);
	Integer(long);
	static Integer& parse(std::string);
	Integer& operator=(const Integer&);
	Integer& operator+=(const Integer&);
	Integer& operator-=(const Integer&);
	Integer& operator*=(const Integer&);
	Integer& operator/=(const Integer&);
	Integer& operator+(const Integer&);
	Integer& operator-(const Integer&);
	Integer& operator*(const Integer&);
	Integer& operator/(const Integer&);
	Integer& operator--(int);
	Integer& operator--();
	Integer& operator++(int);
	Integer& operator++();
	bool operator<(const Integer&);
	bool operator>(const Integer&);
	bool operator<=(const Integer&);
	bool operator>=(const Integer&);
	bool operator==(const Integer&);

	bool operator!=(const Integer&);
	std::string toString();
	~Integer();
	friend std::ostream& operator<<(std::ostream&, const Integer&);



};


#endif // !INTEGER_H