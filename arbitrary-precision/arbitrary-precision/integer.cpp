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
	int digits = (elements(this->integer) - 1) * (MAX_DIGITS * arr->getQuantity());
	int aux = 0;
	for (int i = arr->getCapacity() - arr->getQuantity(); i < arr->getCapacity(); i++) {
		aux += arr->countDigits(i);
	}
	return digits + aux;
}

Integer::Integer() {
	this->integer = nullptr;
}
Integer::Integer(const Integer& integer_b) {
	NodoDoble<Array>* auxiliar = *integer_b.getInteger();
	this->integer = nullptr;

	while (auxiliar != nullptr) {
		append(new Array(*auxiliar->get_data()), this->integer);
		auxiliar = auxiliar->get_next();
	}
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
		if (i < MAX_DIGITS) {
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
				arr->agregar(new int(atoi(string_n.substr(i - MAX_DIGITS, MAX_DIGITS).c_str())));
				prepend(arr, parse->integer);
			}else{
				parse->add_digits(atoi(string_n.substr(i - MAX_DIGITS, MAX_DIGITS).c_str()));
			}
		}
		i -= MAX_DIGITS;
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
			append(new Array(*auxiliar->get_data()), this->integer);
			auxiliar = auxiliar->get_next();
		}

		return *this;
	}
	catch (int) {
		//integer_b is empty!
	}
	

}

Integer& Integer::operator+=(const Integer& integer_b)
{
	*this = (*this + integer_b);
	return *this;
}


Integer& Integer::operator+(const Integer& integer_b)
{
	
	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());

	try {
		if (size_a == 0 || size_b == 0) {
			throw 0;
		}

		Array* auxiliar_array_a = nullptr;
		Array* auxiliar_array_b = nullptr;
		NodoDoble<Array>* list_integer_a = nullptr;
		NodoDoble<Array>* list_integer_b = nullptr;

		if (*this > integer_b) {
			// this
			list_integer_a = last(this->integer);

			// integer_b
			list_integer_b = last(integer_b.integer);
		}
		else {
			// this
			list_integer_b = last(this->integer);

			// integer_b
			list_integer_a = last(integer_b.integer);
		}


		
		// New Integer
		// *this + integer_b
		Array* addition_array = nullptr;
		Integer* integer_addition = new Integer();

		int carry = 0;
		
		int array_a_max = 0;
		int array_b_max = 0;
		int array_a_quantity = 0;
		int array_b_quantity = 0;
		/*
		Lists
		*/
		while (list_integer_a != nullptr && list_integer_b != nullptr) {
			
			/*
			Arrays
			*/
			auxiliar_array_a = list_integer_a->get_data();
			auxiliar_array_b = list_integer_b->get_data();
			array_a_max = auxiliar_array_a->getCapacity();
			array_a_quantity = auxiliar_array_a->getQuantity();
			array_b_max = auxiliar_array_b->getCapacity();
			array_b_quantity = auxiliar_array_b->getQuantity();
			int b = auxiliar_array_b->getCapacity() - 1;
			for (int a = auxiliar_array_a->getCapacity() - 1; (a >= array_a_max - array_a_quantity) || carry; a--) { //Si hay acarreo no puede detenerse la suma
				std::string auxiliar_addition;
				if ((*auxiliar_array_b)[b]) {
					auxiliar_addition = (std::to_string(*(*auxiliar_array_a)[a] + *(*auxiliar_array_b)[b] + carry));
					carry = 0;

					if (auxiliar_addition.length() > MAX_DIGITS) {
						carry = (int)auxiliar_addition[0] - '0';
						auxiliar_addition = auxiliar_addition.substr(1, auxiliar_addition.length() - 1);
					}


					if (addition_array == nullptr) {
						addition_array = new Array;
						addition_array->agregar(new int(std::stoi(auxiliar_addition)));
						prepend(addition_array, integer_addition->integer);
					}
					else {

						integer_addition->add_digits(std::stoi(auxiliar_addition));

					}
				}
				else {
					if (carry) {

						auxiliar_addition = ((*auxiliar_array_a)[a] ? (std::to_string(*(*auxiliar_array_a)[a] + carry)) : std::to_string(carry));
						carry = 0;
						if (auxiliar_addition.length() > MAX_DIGITS) {
							carry = (int)auxiliar_addition[0] - '0';
							auxiliar_addition = auxiliar_addition.substr(1, auxiliar_addition.length() - 1);
						}
						integer_addition->add_digits(stoi(auxiliar_addition));
					}
					else {
						integer_addition->add_digits(*(*auxiliar_array_a)[a]);
					}
					//return *integer_addition;
				}


				b--;


			}

			list_integer_a = list_integer_a->get_previous();
			list_integer_b = list_integer_b->get_previous();

		}


		return *integer_addition;

	}
	catch (int) {
		// At least one of the Integer is empty
	}

}
Integer& Integer::operator*(const Integer& integer_b)
{
	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());
	try {
		if (size_a == 0 || size_b == 0) {
			throw 0;
		}

		Array* auxiliar_array_a = nullptr;
		Array* auxiliar_array_b = nullptr;
		NodoDoble<Array>* list_integer_a = nullptr;
		NodoDoble<Array>* list_integer_b = nullptr;

		if (*this > integer_b) {
			// this
			list_integer_a = last(this->integer);

			// integer_b
			list_integer_b = last(integer_b.integer);
		}
		else {
			// this
			list_integer_b = last(this->integer);

			// integer_b
			list_integer_a = last(integer_b.integer);
		}



		// New Integer
		// *this + integer_b
		Array* multiplication_array = nullptr;
		Integer* integer_multiplication = new Integer();

		int carry = 0;

		int array_a_max = 0;
		int array_b_max = 0;
		int array_a_quantity = 0;
		int array_b_quantity = 0;
		/*
		Lists
		*/
		while (list_integer_a != nullptr && list_integer_b != nullptr) {

			/*
			Arrays
			*/
			auxiliar_array_a = list_integer_a->get_data();
			auxiliar_array_b = list_integer_b->get_data();
			array_a_max = auxiliar_array_a->getCapacity();
			array_a_quantity = auxiliar_array_a->getQuantity();

			array_b_max = auxiliar_array_b->getCapacity();
			array_b_quantity = auxiliar_array_b->getQuantity();

			for (int i = auxiliar_array_b->getCapacity() - 1; (i >= array_b_max - array_b_quantity) || carry; i--) { //Si hay acarreo no puede detenerse la suma
				std::string auxiliar_multiplication;

				if ((*auxiliar_array_a)[i] && (*auxiliar_array_b)[i]) {
					auxiliar_multiplication = (std::to_string(*(*auxiliar_array_a)[i] * *(*auxiliar_array_b)[i] + carry));
					carry = 0;
				}
				else {
					integer_multiplication->add_digits(carry);
					return *integer_multiplication;
				}

				if (auxiliar_multiplication.length() > MAX_DIGITS) {
					carry = (int)auxiliar_multiplication[0] - '0';
					auxiliar_multiplication = auxiliar_multiplication.substr(1, auxiliar_multiplication.length() - 1);
				}


				if (multiplication_array == nullptr) {
					multiplication_array = new Array;
					multiplication_array->agregar(new int(std::stoi(auxiliar_multiplication)));
					prepend(multiplication_array, integer_multiplication->integer);
				}
				else {

					integer_multiplication->add_digits(std::stoi(auxiliar_multiplication));

				}



			}

			list_integer_a = list_integer_a->get_previous();
			list_integer_b = list_integer_b->get_previous();

		}


		return *integer_multiplication;

	}
	catch (int) {
		// At least one of the Integer is empty
	}
}
bool Integer::operator>(const Integer& integer_b) {

	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());

	try {
		if (size_a == 0 || size_b == 0) {
			throw 0;
		}
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
	catch (int) {
		// At least one of the Integer is empty
	}
}

bool Integer::operator<=(const Integer& integer_b)
{
	return (*this == integer_b || *this < integer_b);
}

bool Integer::operator>=(const Integer& integer_b)
{
	return (*this == integer_b || *this > integer_b);
}

bool Integer::operator==(const Integer& integer_b)
{

	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());
	try {
		if (size_a == 0 || size_b == 0) {
			throw 0;
		}
		if (size_a < size_b || size_a > size_b) {
			return false;
		}
		else if (this->cantidadDigitos() > integer_b.cantidadDigitos() || this->cantidadDigitos() < integer_b.cantidadDigitos()) {
			return false;
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
					if (*(*auxiliar_arr_a)[i] < *(*auxiliar_arr_b)[b] || *(*auxiliar_arr_a)[i] > *(*auxiliar_arr_b)[b]) {
						return false;
					}
					b++;
				}

				auxiliar_a = auxiliar_a->get_next();
				auxiliar_b = auxiliar_b->get_next();

			}

			return true;

		}
	}
	catch (int) {
		//At least one of the Integer is empty
	}

}

bool Integer::operator!=(const Integer& integer_b)
{
	return !(*this == integer_b);
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
	try {
		if (integer.getInteger() == nullptr) {
			throw 0;
		}
		NodoDoble<Array>* aux = *integer.getInteger();
		while (aux != nullptr) {
			if (aux->get_previous() == nullptr) {
				Array* auxiliar_array = aux->get_data();
				std::string number = std::to_string(*(*auxiliar_array)[auxiliar_array->getCapacity() - auxiliar_array->getQuantity()]);
				//Signed number
				if (number[0] == '0') { 
					std::stringstream s;
					int digits = aux->get_data()->countDigits(aux->get_data()->getCapacity() - aux->get_data()->getQuantity());
					s << *(aux->get_data());
					std::string str(s.str());
					str = str.substr(MAX_DIGITS - 1, str.length());
					str[0] = '-';
					output << str;
				}
				else {
					std::stringstream s;
					int digits = aux->get_data()->countDigits(aux->get_data()->getCapacity() - aux->get_data()->getQuantity());
					s << *(aux->get_data());
					std::string str(s.str());
					str = str.substr(MAX_DIGITS - digits, str.length());
					output << str;
					//output << *(aux->get_data());
				}
			}
			else {
				output << *(aux->get_data());
			}
			aux = aux->get_next();
		}
		return output;
	}
	catch (int) {
		// Integer is empty
	}
}
