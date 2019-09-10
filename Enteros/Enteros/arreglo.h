#ifndef ARREGLO_H
#define ARREGLO_H
#define MAX_TAM 3;
class Arreglo {

private:

	unsigned int q;
	unsigned int n;
	short int **_arr;

public:

	Arreglo();
	Arreglo(const Arreglo&);
	bool agregar(short int*);
	~Arreglo();
	Arreglo& operator=(const Arreglo&);
	short int* operator[](int) const;

};

#endif // !ARREGLO_H