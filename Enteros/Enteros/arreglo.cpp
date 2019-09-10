#include "arreglo.h"

Arreglo::Arreglo()
{

	this->n = MAX_TAM;
	this->q = 0;
	this->_arr = new short int *[n];
	for (int i = 0; i < n; i++) {
		_arr[i] = nullptr;
		//_arr[i] = new short int(0);
	}

}

Arreglo::Arreglo(const Arreglo& _arr)
{
	this->n = _arr.n;
	this->q = _arr.q;
	this->_arr = new short int*[n];
	
	for (int i = 0; i < n; i++) {
		this->_arr[i] = nullptr;
		//_arr[i] = new short int(0);
	}

	for (int i = 0; i < _arr.q; i++) {
		this->_arr[i] = new short int(*_arr[i]);
	}
}

bool Arreglo::agregar(short int* val)
{
	if (q < n) {
		_arr[q++] = val;
		return true;
	}
	else {
		return false;
	}
	
}

Arreglo::~Arreglo()
{

	for (int i = 0; i < q; i++) {
		delete _arr[i];
	}
	delete[] _arr;

}

Arreglo& Arreglo::operator=(const Arreglo& _arr)
{

	for (int i = 0; i < this->q; i++) {
		delete this->_arr[i];
	}

	this->n = _arr.n;
	this->q = _arr.q;

	for (int i = 0; i < _arr.q; i++) {
		this->_arr[i] = new short int(*_arr[i]);
	}

	return *this;
}

short int*  Arreglo::operator[](int i) const
{
	if (i >= 0 && i < q) {
		return this->_arr[i];
	}
	else {
		return nullptr;
	}
	
}
