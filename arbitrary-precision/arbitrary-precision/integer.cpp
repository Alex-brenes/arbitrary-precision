//integer.h
//Autor: José Alexander Brenes Brenes;Juan Daniel Quirós
//Implementación de la clase para el uso de enteros de precisión arbitraria o bignum
//se incluyen métodos ariméticos y lógicos para el manejo de los enteros
#include "integer.h"

const Integer Integer::ONE = Integer(1);
const Integer Integer::ZERO = Integer(0);
const Integer Integer::ERROR_VALUE = Integer();
void Integer::add_digits(int digit) {
	//Head array
	if (!empty(this->integer)) {
		Array* arr = (*this->integer)->get_data();
		if (arr->getSize() < 0) {
			//New array
			Array* new_arr = new Array;
			new_arr->add(new int(digit));
			prepend(new_arr, this->integer);
		}
		else {
			arr->add(new int(digit));
		}
	}
	else {
		Array* new_arr = new Array;
		new_arr->add(new int(digit));
		prepend(new_arr, this->integer);
	}
}

int Integer::digits() const {
	Array* arr = (*this->integer)->get_data();
	int digits = (elements(this->integer) - 1) * (MAX_DIGITS * arr->getQuantity());
	int aux = 0;
	int digits_arr_cell = 0;
	NodoDoble<Array>* aux_list = (*this->integer);
	while (aux_list) {
		arr = aux_list->get_data();
		for (int i = arr->getCapacity() - arr->getQuantity(); i < arr->getCapacity(); i++) {
			digits_arr_cell = arr->countDigits(i);
			if (digits_arr_cell < MAX_DIGITS && ((*arr)[i - 1] || aux_list->get_previous())) {
				digits_arr_cell += (MAX_DIGITS - digits_arr_cell);
			}
			aux += digits_arr_cell;
		}
		aux_list = aux_list->get_next();
	}

	return digits + aux;
}

Integer::Integer() {
	this->integer = nullptr;
}
Integer::Integer(const Integer& integer_b) {
	if (integer_b.integer == nullptr) {
		this->integer = nullptr;
	}
	else {
		NodoDoble<Array>* auxiliar = *integer_b.getInteger();
		this->integer = nullptr;

		while (auxiliar != nullptr) {
			append(new Array(*auxiliar->get_data()), this->integer);
			auxiliar = auxiliar->get_next();
		}
	}
}
Integer::Integer(int n) {
	this->integer = nullptr;
	Array* arr = new Array;
	arr->add(new int(n));
	prepend(arr, this->integer);
}

Integer::Integer(long n) {
	this->integer = nullptr;
	Array* arr = new Array;
	arr->add(new int(n));
	prepend(arr, this->integer);
}

NodoDoble<Array>** Integer::getInteger() const {
	return this->integer;
}

void Integer::add_one_by_one(int n)
{
	while (n > 0) {
		if (n % 10 == 0) {
			int i = 0;
			while (n % 10 == 0) {
				i++;
				n /= 10;
			}
			add_one_digit((n%10) * pow(10, i));
			n /= 10;
		}
		else {
			add_one_digit(n % 10);
			n /= 10;
		}
	}
}


void Integer::add_one_digit(int z) {
	if (!empty(this->integer)) {

		Array* aux = (*this->integer)->get_data();

		if (aux->countDigits(aux->f_index()) < MAX_DIGITS && (std::to_string(z).length() + aux->countDigits(aux->f_index()) <= MAX_DIGITS)) {
			aux->add_shifted(new int(z));
		}
		else if(std::to_string(z).length() + aux->countDigits(aux->f_index()) > MAX_DIGITS){
			if (!aux->add_one_by_one(z)) {
				this->add_digits(z);
			}
		}
		else {
			this->add_digits(z);
		}
	}
	else {
		this->add_digits(z);
	}
}

void Integer::add_shift(int n)
{
	*this = parse("9" + std::string(n, '0'));
}

void Integer::clear_integer()
{
	clear(integer);
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
				arr->add(new int(atoi(string_n.substr(0, i).c_str())));
				prepend(arr, parse->integer);
			}
			else {
				parse->add_digits(atoi(string_n.substr(0, i).c_str()));
			}
		}
		else {
			if (parse->integer == nullptr) {
				arr = new Array;
				arr->add(new int(atoi(string_n.substr(i - MAX_DIGITS, MAX_DIGITS).c_str())));
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
			throw std::invalid_argument("Integer exception: Integer is empty.");
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
	catch (std::invalid_argument x) {
		// At least one of the Integer is empty
			//return an ERROR VALUE indicator
		std::cout << x.what();
		return *(new Integer(ERROR_VALUE));
	}
	

}

Integer& Integer::operator+=(const Integer& integer_b)
{
	*this = (*this + integer_b);
	return *this;
}

Integer& Integer::operator-=(const Integer& integer_b)
{
	*this = (*this - integer_b);
	return *this;
}

Integer& Integer::operator*=(const Integer& integer_b)
{
	*this = (*this * integer_b);
	return *this;
}


Integer& Integer::operator+(const Integer& integer_b)
{
	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());

	try {
		if (size_a == 0 || size_b == 0) {
			throw std::invalid_argument("Integer exception: Integer is empty.");
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

		//std::cout << *list_integer_a->get_previous()->get_data();

		// New Integer
		// *this + integer_b
		Array* addition_array = nullptr;
		Integer* integer_addition = new Integer();

		int carry = 0;

		int array_a_max = 0;
		int array_b_max = 0;
		int array_a_quantity = 0;
		int array_b_quantity = 0;

		int b = 0;
		int a = 0;


		int a_index = 0;
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
	
			for (a = auxiliar_array_a->getCapacity() - 1; (a >= array_a_max - array_a_quantity) && (*auxiliar_array_b)[b]/* || carry*/; a--) { //Si hay acarreo no puede detenerse la suma
				std::string auxiliar_addition;
				if ((*auxiliar_array_b)[b]) {
					//std::cout << "\na: " << *(*auxiliar_array_a)[a];
					//std::cout << "\n\tpos: " << a;
					a_index = a - 1;
					//std::cout << "\nb: " << *(*auxiliar_array_b)[b];
					//std::cout << "\n\tpos: " << b;

					auxiliar_addition = (std::to_string(*(*auxiliar_array_a)[a] + *(*auxiliar_array_b)[b] + carry));
					carry = 0;

					if (auxiliar_addition.length() > MAX_DIGITS) {
						carry = (int)auxiliar_addition[0] - '0';
						auxiliar_addition = auxiliar_addition.substr(1, auxiliar_addition.length() - 1);
					}

					integer_addition->add_digits(std::stoi(auxiliar_addition));

				}
		
				b--;
				//std::cout << "\naux: " << *integer_addition;
			}
			list_integer_a = list_integer_a->get_previous();
			list_integer_b = list_integer_b->get_previous();

		}
		//std::cout << "\nLo que lleva: " << *integer_addition;
		if (list_integer_a) {
			if (a_index >= 0) {
				list_integer_a = list_integer_a->get_next();
				//std::cout << "\n"<<*list_integer_a->get_data();
			}
			else {
				auxiliar_array_a = list_integer_a->get_data();
				a_index = list_integer_a->get_data()->getCapacity() - 1;

			}
			//std::cout << "\n entero: " << *this;
			while (list_integer_a) {
				while (a_index >= auxiliar_array_a->f_index()) {
					//std::cout << "\nDIGITO: "<<*(*auxiliar_array_a)[a];
					long long cast_addition = (long long) * (*auxiliar_array_a)[a_index] + carry;
					carry = 0;
					if (digits_primitive(cast_addition) > MAX_DIGITS) {
						//Carry
						int pw = pow(10, (digits_primitive(cast_addition) - 1));
						carry = cast_addition / pw;
						long long aa = 1;
						long long aux_cast = cast_addition;
						cast_addition = 0;
						while (aa < pw) {
							cast_addition += (aux_cast % 10) * aa;
							aux_cast /= 10;
							aa *= 10;
						}
					}
					integer_addition->add_digits(cast_addition);
					a_index--;
				}
				list_integer_a = list_integer_a->get_previous();
				if (list_integer_a) {
					auxiliar_array_a = list_integer_a->get_data();
					a_index = auxiliar_array_a->getCapacity() - 1;
				}
			}
		}
		else if ((*auxiliar_array_a)[a_index]) {
			while (a_index >= auxiliar_array_a->f_index()) {
				long long cast_addition = (long long) * (*auxiliar_array_a)[a_index] + carry;
				carry = 0;
				if (digits_primitive(cast_addition) > MAX_DIGITS) {
					//Carry
					int pw = pow(10, (digits_primitive(cast_addition) - 1));
					carry = cast_addition / pw;
					long long aa = 1;
					long long aux_cast = cast_addition;
					cast_addition = 0;
					while (aa < pw) {
						cast_addition += (aux_cast % 10) * aa;
						aux_cast /= 10;
						aa *= 10;
					}
				}
				integer_addition->add_digits(cast_addition);
				a_index--;
			}
		}
		else if(carry){
			integer_addition->add_digits(carry);
		}
		return *integer_addition;

	}
	catch (std::invalid_argument x) {
		// At least one of the Integer is empty
			//return an ERROR VALUE indicator
		std::cout << x.what();
		return *(new Integer(ERROR_VALUE));
	}
}
Integer& Integer::operator-(const Integer& integer_b)
{

	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());

	try {
		if (size_a == 0 || size_b == 0) {
			throw std::invalid_argument("Integer exception: Integer is empty.");
		}
		Array* auxiliar_array_a = nullptr;
		Array* auxiliar_array_b = nullptr;
		NodoDoble<Array>* list_integer_a = nullptr;
		NodoDoble<Array>* list_integer_b = nullptr;
		if (*this == integer_b) {
			return *(new Integer(ZERO));
		}
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
		Array* subtraction_array = nullptr;
		Integer* integer_subtraction = new Integer();

		int carry = 0;


		/*
		Lists
		*/
		//arrays' indices
		int b = 0;
		int a = 0;

		while (list_integer_a != nullptr && list_integer_b != nullptr) {
			auxiliar_array_a = list_integer_a->get_data();
			auxiliar_array_b = list_integer_b->get_data();

			for (a = auxiliar_array_a->getCapacity() - 1, b = auxiliar_array_b->getCapacity() - 1; (*auxiliar_array_a)[a] && (*auxiliar_array_b)[b]; a--, b--) {

				long long cast_subtraction = (long long)*(*auxiliar_array_a)[a] - (long long)*(*auxiliar_array_b)[b] - carry;

				if (cast_subtraction < 0) {
					cast_subtraction += pow(10, MAX_DIGITS);
					carry = 1;
				}
				else {
					carry = 0;
				}

				integer_subtraction->add_digits(cast_subtraction);

			}
			list_integer_a = list_integer_a->get_previous();
			list_integer_b = list_integer_b->get_previous();
		}
		if (list_integer_a) {
			if (a >= 0) {
				list_integer_a = list_integer_a->get_next();
			}
			else {
				auxiliar_array_a = list_integer_a->get_data();
				a = auxiliar_array_a->getCapacity() - 1;
			}
			while (list_integer_a) {
				for (a; a >= auxiliar_array_a->f_index(); a--) {
					long long cast_subtraction = (long long) * (*auxiliar_array_a)[a] - carry;
					if (cast_subtraction < 0) {
						cast_subtraction += pow(10, MAX_DIGITS);
						carry = 1;
					}
					else {
						carry = 0;
					}
					if (cast_subtraction > 0) {
						integer_subtraction->add_digits(cast_subtraction);
					}
					else if (*this < integer_b) { //Add the sign
						integer_subtraction->add_digits(cast_subtraction);
					}
				}
				list_integer_a = list_integer_a->get_previous();
				if (list_integer_a) {
					auxiliar_array_a = list_integer_a->get_data();
					a = auxiliar_array_a->getCapacity() - 1;
				}
			}
		}
		else if ((*auxiliar_array_a)[a]) {
			for (int i = a; i >= auxiliar_array_a->f_index(); i--) {
				long long cast_subtraction = (long long) * (*auxiliar_array_a)[i] - carry;
				if (cast_subtraction < 0) {
					cast_subtraction += pow(10, MAX_DIGITS);
					carry = 1;
				}
				else {
					carry = 0;
				}
				if (cast_subtraction > 0) {
					integer_subtraction->add_digits(cast_subtraction);
				}
			}
		}
		else if (carry){
			integer_subtraction->add_digits(carry);
		}
		
		//Negative case
		if (*this < integer_b) {
			if (((*integer_subtraction->integer)->get_data()->countDigits((*integer_subtraction->integer)->get_data()->f_index())) > MAX_DIGITS) {
				integer_subtraction->add_digits(0);
			}
			else {
				(*integer_subtraction->integer)->get_data()->interchange(new int(*(*(*integer_subtraction->integer)->get_data())[(*integer_subtraction->integer)->get_data()->f_index()] * (-1)), (*integer_subtraction->integer)->get_data()->f_index());
			}
		}
		return *integer_subtraction;

	}
	catch (std::invalid_argument x) {
		// At least one of the Integer is empty
			//return an ERROR VALUE indicator
		std::cout << x.what();
		return *(new Integer(ERROR_VALUE));
	}

}
Integer& Integer::operator*(const Integer& integer_b)
{
	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());
	try {
		if (size_a == 0 || size_b == 0) {
			throw std::invalid_argument("Integer exception: Integer is empty.");
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

		//std::cout << "\n" << *this;
		//std::cout << "\n"<<integer_b;

		NodoDoble<Array>* list_integer_a_aux = nullptr;
		Integer addition_aux;
		int shift = 0;
		int num = 0;
		int b_digit = 0;
		while (list_integer_b != nullptr || carry) {
			if (list_integer_b == nullptr && carry) {
				addition_aux = parse(addition_aux.toString() + std::string(shift, '0'));
				addition_aux.add_digits(carry);
				*integer_multiplication += addition_aux;

				carry = 0;
			}
			else {


				auxiliar_array_b = list_integer_b->get_data();
				for (int b = auxiliar_array_b->getCapacity() - 1; b >= auxiliar_array_b->f_index(); b--) { // B array
					num = *(*auxiliar_array_b)[b];
					while (num > 0) {
						b_digit = num % 10;
						num /= 10;

						//Add the shifts
						std::string shift_len(shift, '0');

						list_integer_a_aux = list_integer_a;
						while (list_integer_a_aux || carry) { // integer_a
							if (!list_integer_a_aux && carry) {
								addition_aux.add_digits(carry);
								carry = 0;
							}
							else {


								auxiliar_array_a = list_integer_a_aux->get_data();
								for (int a = auxiliar_array_a->getCapacity() - 1; a >= auxiliar_array_a->f_index(); a--) { // A array
									long long cast_mult = 0;
									//if (!(*auxiliar_array_a)[a] && carry) {
									//	addition_aux.add_digits(carry);
									//	std::cout << addition_aux;
									//	carry = 0;
									//}
									//else {
									cast_mult = (long long)b_digit * (long long) * (*auxiliar_array_a)[a] + carry;
									carry = 0;

									if (digits_primitive(cast_mult) > MAX_DIGITS) { //Carry
										int pw = pow(10, (digits_primitive(cast_mult) - 1));
										carry = cast_mult / pw;
										long long aa = 1;
										long long aux_cast = cast_mult;
										cast_mult = 0;
										while (aa < pw) {
											cast_mult += (aux_cast % 10) * aa;
											aux_cast /= 10;
											aa *= 10;
										}
									}
									//}


									addition_aux.add_digits(cast_mult);
								}
								list_integer_a_aux = list_integer_a_aux->get_previous();
							}
						}
						//Add the shifts
						addition_aux = parse(addition_aux.toString() + std::string(shift, '0'));
						//--
						//std::cout << "\nNumero: " << addition_aux;
						if (!integer_multiplication->integer) {
							*integer_multiplication = addition_aux;
						}
						else {
							*integer_multiplication += addition_aux;
						}
						addition_aux.clear_integer();
						//std::cout << "\nSumatoria: " << *integer_multiplication;

						shift++;
					}
				}
			}
			list_integer_b = list_integer_b->get_previous();
		}
		return *integer_multiplication;
	}
	catch (std::invalid_argument x) {
		// At least one of the Integer is empty
			//return an ERROR VALUE indicator
		std::cout << x.what();
		return *(new Integer(ERROR_VALUE));
	}
}
Integer& Integer::operator/(const Integer& integer_b)
{
	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());

	try {
		if (size_a == 0 || size_b == 0) {
			throw std::invalid_argument("Integer exception: Integer is empty.");
		}

		if (integer_b ==  ZERO) {
			throw std::domain_error("Math error: Division by zero is undefined.");
		}

		if (*this < integer_b) {
			return *(new Integer(ZERO));
		}

		Array* auxiliar_array_a = nullptr;
		Array* auxiliar_array_b = nullptr;
		NodoDoble<Array>* list_integer_a = *(this)->integer;
		NodoDoble<Array>* list_integer_b = *(integer_b).integer;

		std::string integer_a_str = this->toString();
		int cursor = 0;
		long long divison_cast = (long long)integer_a_str[cursor] - '0';

		std::string division_integer, remain_auxiliar;

		std::string divisor_aux = integer_b.toString();
		std::string dividend_aux = this->toString();

		int division_auxiliar_index = 0;
		int  dividend_length = dividend_aux.length();
		int divisor_length = divisor_aux.length();
			int division_integer_length = dividend_length - divisor_length + 1;

			division_integer.resize(division_integer_length, '0');
			remain_auxiliar = dividend_aux.substr(0, divisor_length);
			for (division_auxiliar_index = 0; division_auxiliar_index < division_integer_length; ) {
				int digit = 0;

				while (remain_auxiliar.size() > divisor_aux.size() || (remain_auxiliar.size() == divisor_aux.size() && remain_auxiliar >= divisor_aux)) {
					digit++;
					remain_auxiliar = (parse(remain_auxiliar) - parse(divisor_aux)).toString();
				}

				division_integer[division_auxiliar_index] = '0' + digit;

				if (remain_auxiliar == "0") {
					remain_auxiliar.clear();
					while (division_auxiliar_index < division_integer_length && dividend_aux[divisor_length + division_auxiliar_index] == '0')
						division_integer[++division_auxiliar_index] = '0';
				}

				remain_auxiliar.reserve(divisor_length + 1);

				while ((remain_auxiliar.size() < divisor_aux.size() || (remain_auxiliar.size() == divisor_aux.size() && remain_auxiliar < divisor_aux)) && division_auxiliar_index < division_integer_length) {
					remain_auxiliar.resize(remain_auxiliar.size() + 1);
					remain_auxiliar[remain_auxiliar.size() - 1] = dividend_aux[divisor_length + division_auxiliar_index];
					division_integer[++division_auxiliar_index] = '0';
				}

			}
			division_auxiliar_index = 0, division_integer_length = division_integer.size() - 1;
			while (division_auxiliar_index < division_integer_length && division_integer[division_auxiliar_index] == '0') {
				++division_auxiliar_index;
			}
			if (division_auxiliar_index) {
				division_integer.erase(0, division_auxiliar_index);
			}
			
			return *new Integer(parse(division_integer));


		Integer* integer_division = nullptr;

	}
	catch (std::domain_error x) {
			//return an ERROR VALUE indicator
		std::cout << x.what();
		return *(new Integer(ERROR_VALUE));
	}
	catch (std::invalid_argument x) {
		// At least one of the Integer is empty
			//return an ERROR VALUE indicator
		std::cout << x.what();
		return *(new Integer(ERROR_VALUE));
	}
}
Integer& Integer::operator--(int)
{
	Integer* older = new Integer(*this);
	(*this) -= ONE;
	return *older;
}
Integer& Integer::operator--()
{
	(*this) -= ONE;
	return (*this);
}
Integer& Integer::operator++(int)
{
	Integer* older = new Integer(*this);
	(*this) += ONE;
	return *older;
}
Integer& Integer::operator++()
{
	(*this) += ONE;
	return (*this);
}
bool Integer::operator>(const Integer& integer_b) {

	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());

	try {
		if (size_a == 0 || size_b == 0) {
			throw std::invalid_argument("Integer exception: Integer is empty.");
		}

		if (this->is_positive() && integer_b.is_negative()) {
			return true;
		}
		else if (this->is_negative() && integer_b.is_positive()) {
			return false;
		}


		if (size_a > size_b) {
			return true;
		}
		else if (size_a < size_b) {
			return false;
		}
		else if (this->digits() > integer_b.digits()) {
			return true;
		}
		else if (this->digits() < integer_b.digits()) {
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
					if (*(*auxiliar_arr_a)[i] > * (*auxiliar_arr_b)[b]) {
						return true;
					}
					else if (*(*auxiliar_arr_a)[i] < *(*auxiliar_arr_b)[b]) {
						return false;
					}
					b++;
				}

				auxiliar_a = auxiliar_a->get_next();
				auxiliar_b = auxiliar_b->get_next();

			}

			return false;
		}
	}
	catch (std::invalid_argument x) {
		// At least one of the Integer is empty
			//return an ERROR VALUE indicator
		std::cout << x.what();
		return false;
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
			throw std::invalid_argument("Integer exception: Integer is empty.");
		}
		if (size_a < size_b || size_a > size_b) {
			return false;
		}
		else if (this->digits() > integer_b.digits() || this->digits() < integer_b.digits()) {
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
	catch (std::invalid_argument x) {
		// At least one of the Integer is empty
			//return an ERROR VALUE indicator
		std::cout << x.what();
		return false;
	}

}

bool Integer::operator==(const Integer& integer_b) const
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
		else if (this->digits() > integer_b.digits() || this->digits() < integer_b.digits()) {
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
					if (*(*auxiliar_arr_a)[i] < *(*auxiliar_arr_b)[b] || *(*auxiliar_arr_a)[i] > * (*auxiliar_arr_b)[b]) {
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
	catch (std::invalid_argument x) {
		// At least one of the Integer is empty
			//return an ERROR VALUE indicator
		std::cout << x.what();
		return false;
	}
}


bool Integer::is_positive() const
{
	return (*(*(*this->integer)->get_data())[(*this->integer)->get_data()->f_index()] >= 0 || (*(*(*this->integer)->get_data())[(*this->integer)->get_data()->f_index()] != 0 && ((*this->integer)->get_next() != nullptr || (*this->integer)->get_data()->f_index() < MAX_TAM - 1)));
}

bool Integer::is_negative() const
{
	return (*(*(*this->integer)->get_data())[(*this->integer)->get_data()->f_index()] < 0 || (*(*(*this->integer)->get_data())[(*this->integer)->get_data()->f_index()] == 0 && ((*this->integer)->get_next() != nullptr || (*this->integer)->get_data()->f_index() < MAX_TAM - 1)));
}

int Integer::digits_primitive(long long n)
{
	int counter = 1;
	long long auxiliar = n;
	while (auxiliar >= 10) {
		auxiliar /= 10;
		counter++;
	}
	return counter;
}

void Integer::add_with_carry(int digit)
{
	add_one_by_one(digit);
	(*this->integer)->get_data()->reduceSize();
}

bool Integer::operator!=(const Integer& integer_b)
{
	try {
		if (integer_b.integer == nullptr) {
			throw std::invalid_argument("Integer exception: Integer is empty.");
		}
		return !(*this == integer_b);
	}
	catch (std::invalid_argument x) {
		std::cout << x.what();
		return false;
	}
}

std::string Integer::toString() const
{
	std::stringstream s;
	s << *this;
	return s.str();
}


bool Integer::operator<(const Integer& integer_b)
{
	
	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());
	try {
		if (size_a == 0 || size_b == 0) {
			throw std::invalid_argument("Integer exception: Integer is empty.");
		}


		if (this->is_positive() && integer_b.is_negative()) {
			return false;
		}
		else if (this->is_negative() && integer_b.is_positive()) {
			return true;
		}

		if (size_a < size_b) {
			return true;
		}
		else if (size_a > size_b) {
			return false;
		}
		else if (this->digits() < integer_b.digits()) {
			return true;
		}
		else if (this->digits() > integer_b.digits()) {
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
					if (*(*auxiliar_arr_a)[i] < *(*auxiliar_arr_b)[b]) {
						return true;
					}
					else if (*(*auxiliar_arr_a)[i] > *(*auxiliar_arr_b)[b]){
						return false;
					}
					b++;
				}

				auxiliar_a = auxiliar_a->get_next();
				auxiliar_b = auxiliar_b->get_next();

			}

			return false;

		}
	}
	catch (std::invalid_argument x) {
		// At least one of the Integer is empty
			//return an ERROR VALUE indicator
		std::cout << x.what();
		return false;
	}
	

}

Integer::~Integer() {
	clear(integer);
	delete integer;
}

std::ostream& operator<<(std::ostream& output, const Integer& integer) {
	try {
		if (integer.getInteger() == nullptr) {
			throw std::invalid_argument("Integer exception: Integer is empty.");
		}
		NodoDoble<Array>* aux = *integer.getInteger();
		while (aux != nullptr) {
			if (aux->get_previous() == nullptr) {
				Array* auxiliar_array = aux->get_data();
				int first = auxiliar_array->getCapacity() - auxiliar_array->getQuantity();
				std::string number = std::to_string(*(*auxiliar_array)[auxiliar_array->getCapacity() - auxiliar_array->getQuantity()]);
				//Signed number
				if (number[0] == '0' && (aux->get_next() || (*auxiliar_array)[auxiliar_array->getCapacity() - auxiliar_array->getQuantity() + 1])) {
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
	catch (std::invalid_argument x) {
		// At least one of the Integer is empty
			//return an ERROR VALUE indicator
		output << x.what();
		return output;
	}
}
