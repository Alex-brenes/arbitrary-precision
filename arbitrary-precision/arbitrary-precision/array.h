#ifndef ARRAY_H
#define ARRAY_H
#define MAX_TAM 3;
#include <iostream>
class Array {

private:

	unsigned int size;
	unsigned int capacity;
	int **_arr;

public:

	Array();
	Array(const Array&);
	int getCapacity() const;
	int getSize() const;
	bool agregar(int*);
	~Array();
	Array& operator=(const Array&);
	int* operator[](int) const;

};

std::ostream& operator<<(std::ostream&, const Array&);

#endif // !ARRAY_H