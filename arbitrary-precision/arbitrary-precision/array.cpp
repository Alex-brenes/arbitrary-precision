#include "array.h"

Array::Array()
{
	this->capacity = MAX_TAM;
	this->size = capacity - 1;
	this->_arr = new int *[capacity];
	for (int i = 0; i < capacity; i++) {
		_arr[i] = nullptr;
	}
}

Array::Array(const Array& _arr)
{
	this->capacity = _arr.capacity;
	this->size = _arr.size;
	this->_arr = new int*[capacity];
	for (int i = 0; i < capacity; i++) {
		this->_arr[i] = nullptr;
	}
	for (int i = _arr.capacity - 1; i > _arr.size; i--) {
		if (_arr[i]) {
			this->_arr[i] = new int(*_arr[i]);
		}
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

int Array::getQuantity() const
{
	return capacity - (size + 1);
}

int Array::countDigits(int index)
{
	int counter = 1;
	int auxiliar = *(*this)[index];
	while (auxiliar > 10) {
		auxiliar /= 10;
		counter++;
	}
	return counter;
}

bool Array::agregar(int* val)
{
	//End
	if (size >= 0) {
		if (this->getQuantity() == 0) {
			_arr[size--] = val;
		}
		else if (std::to_string(*_arr[size + 1]).length() < 9) {
			
			_arr[size + 1] = new int(atoi((std::to_string(*val) + std::to_string(*_arr[size + 1])).c_str()));
		}
		else {
			_arr[size--] = val;
		}
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

	for (int i = capacity-1; i > size; i--) {
		delete _arr[i];
	}
	delete[] _arr;

}

Array& Array::operator=(const Array& _arr)
{
	for (int i = capacity - 1; i > size; i--) {
		delete this->_arr[i];
	}
	this->capacity = _arr.capacity;
	this->size = _arr.size;
	for (int i = capacity - 1; i > size; i--) {
		this->_arr[i] = new int(*_arr[i]);
	}
	return *this;
}

int*  Array::operator[](int i) const
{
	if (i >= size && i < capacity) {
		return this->_arr[i];
	}
	else {
		return nullptr;
	}
}

std::ostream& operator<<(std::ostream& output, const Array& arr)
{
	for (int i = 0; i < arr.getCapacity(); i++) {
		if (arr[i] != nullptr) {
			output << *arr[i];
		}
	}
	return output;
}
