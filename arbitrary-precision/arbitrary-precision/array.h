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
	bool agregar(int*);
	~Array();
	Array& operator=(const Array&);
	int* operator[](int) const;


};

std::ostream& operator<<(std::ostream&, const Array&);

#endif // !ARRAY_H