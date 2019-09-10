#include "array.h"

Array::Array()
{

	this->capacity = MAX_TAM;
	this->size = capacity - 1;
	this->_arr = new int *[capacity];
	for (int i = 0; i < capacity; i++) {
		_arr[i] = nullptr;
		//_arr[i] = new short int(0);
	}

}

Array::Array(const Array& _arr)
{
	this->capacity = _arr.capacity;
	this->size = _arr.size;
	this->_arr = new int*[capacity];
	
	for (int i = 0; i < capacity; i++) {
		this->_arr[i] = nullptr;
		//_arr[i] = new short int(0);
	}

	for (int i = 0; i < _arr.size; i++) {
		this->_arr[i] = new int(*_arr[i]);
	}
}

int Array::getCapacity() const
{
	return capacity;
}

int Array::getSize() const
{
	return size;
}

bool Array::agregar(int* val)
{
	//End
	std::cout << size;
	if (size >= 0) {
		_arr[size--] = val;
		return true;
	}
	else {
		return false;
	}

	//Begin
	//if (q < n) {
	//	_arr[q++] = val;
	//	return true;
	//}
	//else {
	//	return false;
	//}
	
}

Array::~Array()
{

	for (int i = 0; i < size; i++) {
		delete _arr[i];
	}
	delete[] _arr;

}

Array& Array::operator=(const Array& _arr)
{

	for (int i = 0; i < this->size; i++) {
		delete this->_arr[i];
	}

	this->capacity = _arr.capacity;
	this->size = _arr.size;

	for (int i = 0; i < _arr.size; i++) {
		this->_arr[i] = new int(*_arr[i]);
	}

	return *this;
}

int*  Array::operator[](int i) const
{
	if (i >= 0 && i < capacity   /*capacity - size*/) {
		return this->_arr[i];
	}
	else {
		return nullptr;
	}
	
}

std::ostream& operator<<(std::ostream& output, const Array& arr)
{
	for (int i = arr.getCapacity() - 1; i >= 0 /*arr.getCapacity() - arr.getSize()*/; i--) {
		output << *arr[i];
	}
	return output;
}
