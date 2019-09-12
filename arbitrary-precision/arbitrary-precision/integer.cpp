#include "integer.h"

void Integer::add_digits(int digit) {
	//Head array
	Array * arr = (*this->integer)->get_data();
	if (arr->getSize() < 0) {
		//New array
		Array* new_arr = new Array;
		new_arr->agregar(new int(digit));
		prepend(new_arr, this->integer);
	}
	else {
		arr->agregar(new int(digit));
	}

}

int Integer::cantidadDigitos() const {
	Array* arr = (*this->integer)->get_data();
	int digits = (elements(this->integer) - 1) * (9 * arr->getQuantity());
	int aux = 0;
	for (int i = arr->getCapacity() - arr->getQuantity(); i < arr->getCapacity(); i++) {
		aux += arr->countDigits(i);
	}
	return digits + aux;
}

Integer::Integer() {
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

Integer& Integer::operator=(const Integer& integer_b)
{
	try {
		
		if (integer_b.integer == nullptr) {
			throw 0;
		}
		clear(this->integer);
		delete integer;


		NodoDoble<Array>* auxiliar = *integer_b.getInteger();
		integer = nullptr;

		while (auxiliar != nullptr) {
			prepend(new Array(*auxiliar->get_data()), this->integer);
			auxiliar = auxiliar->get_next();
		}

		return *this;
	}
	catch (int) {
		//integer_b is empty!
	}
	

}



Integer& Integer::operator+(const Integer& integer_b)
{



	return *this;

}
bool Integer::operator>(const Integer& integer_b) {

	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());

	if (size_a > size_b) {
		return true;
	}
	else if (size_a < size_b) {
		return false;
	}
	else if (this->cantidadDigitos() > integer_b.cantidadDigitos()) {
		return true;
	}
	else {


		//Misma cantidad de nodos y dígitos
			/*
			Se revisa desde el primer nodo y se detiene en el momento en el que
			uno de los dos dígitos sea mayor al otro.
			*/

		NodoDoble <Array>* auxiliar_a = *this->integer;
		NodoDoble <Array>* auxiliar_b = *integer_b.integer;

		Array* auxiliar_arr_a;
		Array* auxiliar_arr_b;

		while (auxiliar_a != nullptr && auxiliar_b != nullptr) {
			auxiliar_arr_a = auxiliar_a->get_data();
			auxiliar_arr_b = auxiliar_b->get_data();
			int b = auxiliar_arr_b->getCapacity() - auxiliar_arr_b->getQuantity();

			for (int i = auxiliar_arr_a->getCapacity() - auxiliar_arr_a->getQuantity();
				i < auxiliar_arr_a->getCapacity() && b < auxiliar_arr_b->getCapacity(); i++) {
				int a = *(*auxiliar_arr_a)[i];
				int j = *(*auxiliar_arr_b)[b];
				if (*(*auxiliar_arr_a)[i] > * (*auxiliar_arr_b)[b]) {
					return true;
				}
				b++;
			}

			auxiliar_a = auxiliar_a->get_next();
			auxiliar_b = auxiliar_b->get_next();

		}

		return false;
	}

}


bool Integer::operator<(const Integer& integer_b)
{
	
	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());
	try {
		if (size_a == 0 || size_b == 0) {
			throw 0;
		}
		if (size_a < size_b) {
			return true;
		}
		else if (size_a > size_b) {
			return false;
		}
		else {

			//Misma cantidad de nodos
				/*
				Se revisa desde el primer nodo y se detiene en el momento en el que
				uno de los dos dígitos sea mayor al otro.
				*/

			NodoDoble <Array>* auxiliar_a = *this->integer;
			NodoDoble <Array>* auxiliar_b = *integer_b.integer;

			Array* auxiliar_arr_a;
			Array* auxiliar_arr_b;

			while (auxiliar_a != nullptr && auxiliar_b != nullptr) {
				auxiliar_arr_a = auxiliar_a->get_data();
				auxiliar_arr_b = auxiliar_b->get_data();
				int b = auxiliar_arr_b->getCapacity() - auxiliar_arr_b->getQuantity();

				for (int i = auxiliar_arr_a->getCapacity() - auxiliar_arr_a->getQuantity();
					i < auxiliar_arr_a->getCapacity() && b < auxiliar_arr_b->getCapacity(); i++) {
					if (*(*auxiliar_arr_a)[i] < *(*auxiliar_arr_b)[b]) {
						return true;
					}
					b++;
				}

				auxiliar_a = auxiliar_a->get_next();
				auxiliar_b = auxiliar_b->get_next();

			}

			return false;

		}
	}
	catch (int) {
		//At least one of the Integer is empty
	}
	

}

Integer::~Integer() {
	clear(integer);
	delete integer;
}

std::ostream& operator<<(std::ostream& output, const Integer& integer) {
	NodoDoble<Array>* aux = last(integer.getInteger());
	while (aux != nullptr) {
		output << *(aux->get_data());
		aux = aux->get_previous();
	}
	return output;
}
