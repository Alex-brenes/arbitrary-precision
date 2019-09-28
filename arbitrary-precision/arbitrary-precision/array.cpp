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
	//for (int i = _arr.capacity - 1; i > _arr.size; i--) {
	//	if (_arr[i]) {
	//		this->_arr[i] = new int(*_arr[i]);
	//	}
	//}

	for (int i = _arr.capacity - _arr.getQuantity(); i < _arr.capacity; i++) {
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

int Array::getQuantity() const
{
	return capacity - (size + 1);
}

int Array::countDigits(int index) const
{
	int counter = 1;
	int auxiliar = *(*this)[index];
	while (auxiliar >= 10) {
		auxiliar /= 10;
		counter++;
	}
	return counter;
}

bool Array::add(int* val)
{
	//End
	if (size >= 0) {
		if (size + 1 < MAX_TAM) {
			//std::cout << "\n" << *_arr[size + 1];
		}
		if (this->getQuantity() == 0) {
			_arr[size--] = val;
		}
		//Si se quiere meter con un solo cero por celda descomentar esto
		//else if (std::to_string(*_arr[size + 1]).length() < 9) {
		//	_arr[size + 1] = new int(atoi((std::to_string(*val) + std::to_string(*_arr[size + 1])).c_str()));
		//}
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

bool Array::add_one_by_one(int& val)
{
	int i = this->countDigits(size + 1);
	while (i < MAX_DIGITS) {
		add_shifted(new int(val % 10));
		val /= 10;
		if (val <= 0 && i <= MAX_DIGITS) {
			return true;
		}
		i++;
	}
	return false;
}

bool Array::add_shifted(int* val)
{
	if (std::to_string(*_arr[size + 1]).length() < MAX_DIGITS) {
		//std::cout << "\n" << *_arr[size + 1];
		_arr[size + 1] = new int(atoi((std::to_string(*val) + std::to_string(*_arr[size + 1])).c_str()));
		return true;
	}
	return false;
}

bool Array::interchange(int* n, int index)
{
	if (index >= size && index < capacity) {
		delete this->_arr[index];
		this->_arr[index] = n;
	}
	else {
		return false;
	}
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

int Array::f_index()
{ //Returns the first non-null position in the array
	return this->getCapacity() - this->getQuantity();
}

std::ostream& operator<<(std::ostream& output, const Array& arr)
{
	//for (int i = 0; i < arr.getCapacity(); i++) {
	//	if (arr[i] != nullptr) {
	//		output << *arr[i];
	//	}
	//}
	//return output;
	for (int i = arr.getCapacity() - arr.getQuantity(); i < arr.getCapacity(); i++) {
		if (arr[i] != nullptr) {
			if (arr.countDigits(i) < MAX_DIGITS) {
				output << std::string(MAX_DIGITS - arr.countDigits(i), '0');
			}
			output << *arr[i];
		}
	}
	return output;
}
