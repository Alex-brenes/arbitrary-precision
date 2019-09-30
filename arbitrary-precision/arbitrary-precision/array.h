//array.cpp
//Autor: Jos� Alexander Brenes Brenes; Juan Daniel Quir�s
//Clase que contiene un arreglo de tama�o 8 capaz de almacenar hasta 72 d�gitos
#ifndef ARRAY_H
#define ARRAY_H
#define MAX_TAM 8
#define MAX_DIGITS 9
#include <iostream>
#include <string>
class Array {

private:

	int size;
	unsigned int capacity;
	int **_arr;

public:

	Array();
	Array(const Array&);
	int getCapacity() const;
	int getSize() const;
	int getQuantity() const;
	int countDigits(int) const;
	bool add(int*);
	bool add_one_by_one(int&);
	bool add_shifted(int*);
	bool interchange(int*, int);
	~Array();
	Array& operator=(const Array&);
	int* operator[](int) const;
	int f_index();
	void reduceSize();
};

std::ostream& operator<<(std::ostream&, const Array&);

#endif // !ARRAY_H