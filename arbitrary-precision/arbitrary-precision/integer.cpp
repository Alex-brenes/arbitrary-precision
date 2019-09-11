#include "integer.h"

void Integer::add_digits(int digit) {

	Array * arr = (*this->integer)->get_data();
	if (arr->getSize() < 0) {

	}
	else {
		arr->agregar(new int(digit));
	}

}

Integer::Integer() {
	Array* arr = new Array;
	this->integer = nullptr;
}
Integer::Integer(int n) {
	Array* arr = new Array;
	arr->agregar(new int(n));
	prepend(arr, this->integer);
}

Integer::Integer(long n) {
	Array* arr = new Array;
	arr->agregar(new int(n));
	prepend(arr, this->integer);
}

NodoDoble<Array>** Integer::getInteger() const {
	return this->integer;
}

Integer& Integer::parse(std::string string_n)
{
	//Parse string
	Integer* parse = new Integer();

	//First array
	Array* arr = nullptr;

	int i = string_n.length();
	while (i > 0) {
		if (i < 9) {
			if (parse->integer == nullptr) {
				arr = new Array;
				arr->agregar(new int(atoi(string_n.substr(0, i).c_str())));
				prepend(arr, parse->integer);
			}
			else {
				parse->add_digits(atoi(string_n.substr(0, i).c_str()));
			}
		}
		else {
			if (parse->integer == nullptr) {
				arr = new Array;
				arr->agregar(new int(atoi(string_n.substr(i - 9, 9).c_str())));
				prepend(arr, parse->integer);
			}else{
				parse->add_digits(atoi(string_n.substr(i - 9, 9).c_str()));
			}
		}
		i -= 9;
	}
	return *parse;
}

Integer::~Integer() {
	clear(integer);
	delete integer;
}

std::ostream& operator<<(std::ostream& output, const Integer& integer) {
	NodoDoble<Array>* aux = *(integer.getInteger());
	while (aux != nullptr) {
		output << *(aux->get_data());
		aux = aux->get_next();
	}
	return output;
}
