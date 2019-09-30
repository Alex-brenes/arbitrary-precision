//integer.h
//Autor: José Alexander Brenes Brenes;Juan Daniel Quirós
//Clase para enteros de precisión arbitraria o bignum
//se incluyen métodos ariméticos y lógicos para el manejo de los enteros
#ifndef INTEGER_H
#define INTEGER_H
#include <string>
#include <sstream>
#include <math.h>
#include "doublelinkedlist.h"
#include "array.h"
#define MAX_DIGITS 9
#define MAX_NUM_PER_CELL 999999999
//#define ZERO 0
//#define ONE 1

class Integer {

private:
	static const Integer ERROR_VALUE;
	NodoDoble<Array>** integer;
	void add_digits(int);
	int digits() const;
	NodoDoble<Array>** getInteger() const;
	void add_one_by_one(int);
	void add_one_digit(int);
	void add_shift(int);
	void clear_integer();
	bool operator==(const Integer&) const;
	bool is_positive() const;
	bool is_negative() const;
	int digits_primitive(long long);
	void add_with_carry(int);
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
	std::string toString() const;
	~Integer();
	friend std::ostream& operator<<(std::ostream&, const Integer&);



};


#endif // !INTEGER_H