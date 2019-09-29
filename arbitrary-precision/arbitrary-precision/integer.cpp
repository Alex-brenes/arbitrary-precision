#include "integer.h"

const Integer Integer::ONE = Integer(1);
const Integer Integer::ZERO = Integer(0);

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
	NodoDoble<Array>* auxiliar = *integer_b.getInteger();
	this->integer = nullptr;

	while (auxiliar != nullptr) {
		append(new Array(*auxiliar->get_data()), this->integer);
		auxiliar = auxiliar->get_next();
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
	//std::cout << *this;
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

		//while (list_integer_a != nullptr && list_integer_b != nullptr) {
		//	auxiliar_array_a = list_integer_a->get_data();
		//	auxiliar_array_b = list_integer_b->get_data();
		//	array_a_max = auxiliar_array_a->getCapacity();
		//	array_a_quantity = auxiliar_array_a->getQuantity();
		//	array_b_max = auxiliar_array_b->getCapacity();
		//	array_b_quantity = auxiliar_array_b->getQuantity();
		//	b = auxiliar_array_b->getCapacity() - 1;
		//	a = auxiliar_array_a->getCapacity() - 1;

		//	while (a >= auxiliar_array_a->f_index() && b >= auxiliar_array_b->f_index()) {

		//		long long cast_addition = (long long) * (*auxiliar_array_a)[a] + (long long) * (*auxiliar_array_b)[b] + carry;
		//		carry = 0;

		//		if (digits_primitive(cast_addition) > MAX_DIGITS) {
		//			//Carry
		//			int pw = pow(10, (digits_primitive(cast_addition) - 1));
		//			carry = cast_addition / pw;
		//			long long aa = 1;
		//			long long aux_cast = cast_addition;
		//			cast_addition = 0;
		//			while (aa < pw) {
		//				cast_addition += (aux_cast % 10) * aa;
		//				aux_cast /= 10;
		//				aa *= 10;
		//			}
		//		}

		//		integer_addition->add_digits(cast_addition);
		//		std::cout << *integer_addition;
		//		a--;
		//		b--;
		//	}
		//	list_integer_a = list_integer_a->get_previous();
		//	list_integer_b = list_integer_b->get_previous();
		//}
		//if (list_integer_a) {
		//	std::cout << *(*list_integer_a->get_data())[7];
		//	if (a >= 0) {
		//		list_integer_a = list_integer_a->get_next();
		//	}
		//	else {
		//		auxiliar_array_a = list_integer_a->get_data();
		//		a = list_integer_a->get_data()->getCapacity() - 1;

		//	}
		//	while (list_integer_a) {
		//		while (a >= auxiliar_array_a->f_index()) {
		//			long long cast_addition = (long long) *(*auxiliar_array_a)[a] + carry;
		//			carry = 0;
		//			if (digits_primitive(cast_addition) > MAX_DIGITS) {
		//				//Carry
		//				int pw = pow(10, (digits_primitive(cast_addition) - 1));
		//				carry = cast_addition / pw;
		//				long long aa = 1;
		//				long long aux_cast = cast_addition;
		//				cast_addition = 0;
		//				while (aa < pw) {
		//					cast_addition += (aux_cast % 10) * aa;
		//					aux_cast /= 10;
		//					aa *= 10;
		//				}
		//			}
		//			integer_addition->add_digits(cast_addition);
		//			a--;
		//		}
		//		list_integer_a = list_integer_a->get_previous();
		//		if (list_integer_a) {
		//			auxiliar_array_a = list_integer_a->get_data();
		//			a = auxiliar_array_a->getCapacity() - 1;
		//		}
		//	}
		//}
		//else if ((*auxiliar_array_a)[a]){
		//	while (a >= auxiliar_array_a->f_index()) {
		//		long long cast_addition = (long long) * (*auxiliar_array_a)[a] + carry;
		//		carry = 0;
		//		if (digits_primitive(cast_addition) > MAX_DIGITS) {
		//			//Carry
		//			int pw = pow(10, (digits_primitive(cast_addition) - 1));
		//			carry = cast_addition / pw;
		//			long long aa = 1;
		//			long long aux_cast = cast_addition;
		//			cast_addition = 0;
		//			while (aa < pw) {
		//				cast_addition += (aux_cast % 10) * aa;
		//				aux_cast /= 10;
		//				aa *= 10;
		//			}
		//		}
		//		integer_addition->add_digits(cast_addition);
		//		a--;
		//	}
		//}
		//else {
		//	integer_addition->add_digits(carry);
		//}
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
					//if (addition_array == nullptr) {
					//	addition_array = new Array;
					//	addition_array->add(new int(std::stoi(auxiliar_addition)));
					//	prepend(addition_array, integer_addition->integer);
					//}
					//else {

					//	integer_addition->add_digits(std::stoi(auxiliar_addition));

					//}
				}
				else {
					//std::cout << "\n Se agregan los demas numeros de a sumando solo con el acarreo";
					//if (carry && (!list_integer_a->get_previous())) {

					//	auxiliar_addition = ((*auxiliar_array_a)[a] ? (std::to_string(*(*auxiliar_array_a)[a] + carry)) : std::to_string(carry));
					//	carry = 0;
					//	if (auxiliar_addition.length() > MAX_DIGITS) {
					//		carry = (int)auxiliar_addition[0] - '0';
					//		auxiliar_addition = auxiliar_addition.substr(1, auxiliar_addition.length() - 1);
					//	}
					//	integer_addition->add_digits(stoi(auxiliar_addition));
					//}
					//else if ((*auxiliar_array_a)[a]) {
					//	integer_addition->add_digits(*(*auxiliar_array_a)[a]);
					//}
					//else if ((*auxiliar_array_a)[a] && carry) {
					//	long long f = carry + *(*auxiliar_array_a)[a];
					//	carry = 0;
					//	if (digits_primitive(f) > MAX_DIGITS) { //Carry
					//		int pw = pow(10, (digits_primitive(f) - 1));
					//		carry = f / pw;
					//		long long aa = 1;
					//		long long aux_cast = f;
					//		f = 0;
					//		while (aa < pw) {
					//			f += (aux_cast % 10) * aa;
					//			aux_cast /= 10;
					//			aa *= 10;
					//		}
					//	}
					//	integer_addition->add_digits(f);
					//}
					////return *integer_addition;
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
					//std::cout << "\nDIGITO: "<<*(*auxiliar_array_a)[a_index];
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
	catch (int) {
		// At least one of the Integer is empty
	}

}
Integer& Integer::operator-(const Integer& integer_b)
{

	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());

	try {
		if (size_a == 0 || size_b == 0) {
			throw 0;
		}

		if (*this == integer_b) {
			return *(new Integer(ZERO));
		}

		Array auxiliar_array_a;
		Array* auxiliar_array_b = nullptr;

		NodoDoble<Array>* list_integer_a = last(this->integer);
		NodoDoble<Array>* list_integer_a_prev = last(this->integer);
		NodoDoble<Array>* list_integer_b = last(integer_b.integer);
		NodoDoble<Array>* list_integer_b_prev = last(integer_b.integer);


		// New Integer
		// *this + integer_b
		Array* subtraction_array = nullptr;
		Integer* integer_subtraction = new Integer();

		int borrow = 0;

		int array_a_max = 0;
		int array_b_max = 0;
		int array_a_quantity = 0;
		int array_b_quantity = 0;
		/*
		Lists
		*/
		//arrays' indices
		int b = 0;
		int a = 0;
		while (list_integer_a != nullptr && list_integer_b != nullptr) {
			/*
			Arrays
			*/

			auxiliar_array_a = *list_integer_a->get_data();
			array_a_max = auxiliar_array_a.getCapacity();
			array_a_quantity = auxiliar_array_a.getQuantity();
			
			auxiliar_array_b = list_integer_b->get_data();
			array_b_max = auxiliar_array_b->getCapacity();
			array_b_quantity = auxiliar_array_b->getQuantity();

			for (a = auxiliar_array_a.getCapacity() - 1, b = auxiliar_array_b->getCapacity() - 1; a >= auxiliar_array_a.getCapacity() - auxiliar_array_a.getQuantity() && b >= auxiliar_array_b->getCapacity() - auxiliar_array_b->getQuantity(); a--, b--) {
				int subtraction = 0;
				if (*auxiliar_array_a[a] >= *(*auxiliar_array_b)[b]) { // Positive subtraction
					subtraction = *auxiliar_array_a[a] - *(*auxiliar_array_b)[b];
				}
				else if (a > auxiliar_array_a.getCapacity() - auxiliar_array_a.getQuantity() || list_integer_a->get_previous()) { // Borrow
					
					NodoDoble<Array>* temp_auxliar_a = list_integer_a;
					Array* temp_aux_array_a = &auxiliar_array_a;
					int i = a - 1;
					// Nodes
					while (subtraction == 0 && temp_auxliar_a) {
						//Array
						while (i >= 0 && subtraction == 0) {
							if ((*temp_aux_array_a)[i]) {
								if (*(*temp_aux_array_a)[i] > 0) {
									temp_aux_array_a->interchange(new int(*(*temp_aux_array_a)[i] - 1), i);
									std::string subtraction_string = "1" + std::to_string(*auxiliar_array_a[a]);
									subtraction = (long long)(std::stoll(subtraction_string)) - (long long) * (*auxiliar_array_b)[b];
								}
							}
							i--;
						}
						temp_auxliar_a = temp_auxliar_a->get_previous();
						if (temp_auxliar_a) {
							temp_aux_array_a = temp_auxliar_a->get_data();
						}
					}

				}
				else { // Negative
					subtraction = *auxiliar_array_a[a] - *(*auxiliar_array_b)[b];
				}
				if (integer_subtraction->integer == nullptr) {
					subtraction_array = new Array();
					subtraction_array->add(new int(subtraction));
					prepend(subtraction_array, integer_subtraction->integer);
				}
				else {
					integer_subtraction->add_digits(subtraction);
				}
			}
			list_integer_a_prev = list_integer_a;
			list_integer_a = list_integer_a->get_next();
			list_integer_b_prev = list_integer_b;
			list_integer_b = list_integer_b->get_next();
		}

		//Check whether are digits left in some Integer
		
		if (list_integer_a_prev != nullptr && list_integer_b == nullptr && (*list_integer_a_prev->get_data())[a]) { // Positive
			Array* aux_p = list_integer_a_prev->get_data();
			while (list_integer_a_prev) {
				aux_p = list_integer_a_prev->get_data();
				while ((*aux_p)[a]) {
					integer_subtraction->add_digits(*(*aux_p)[a--]);
				}
				list_integer_a_prev = list_integer_a_prev->get_next();
				a = aux_p->getCapacity() - 1;
			}
		}
		else if (list_integer_b_prev != nullptr && list_integer_a == nullptr) { // Negative
			Array* aux_p = list_integer_b_prev->get_data();
			while (list_integer_b_prev) {
				aux_p = list_integer_b_prev->get_data();
				while ((*aux_p)[b]) {
					if (std::to_string(*(*aux_p)[b]).length() < MAX_DIGITS) {
						integer_subtraction->add_digits((-1) * *(*aux_p)[b--]);
					}
					else if(list_integer_b_prev->get_next() == nullptr && (*aux_p)[b - 1] == nullptr){
						integer_subtraction->add_digits(*(*aux_p)[b--]);
						integer_subtraction->add_digits(0);
					}
					else {
						integer_subtraction->add_digits(*(*aux_p)[b--]);
					}
				}
				list_integer_b_prev = list_integer_b_prev->get_next();
				b = aux_p->getCapacity() - 1;
			}
		}
		//while (list_integer_a != nullptr && list_integer_b != nullptr) {

		//	/*
		//	Arrays
		//	*/
		//	if (list_integer_a) {
		//		list_integer_a = list_integer_a;
		//		auxiliar_array_a = *list_integer_a->get_data();
		//		array_a_max = auxiliar_array_a.getCapacity();
		//		array_a_quantity = auxiliar_array_a.getQuantity();
		//	}
		//	if (list_integer_b) {
		//		list_integer_b = list_integer_b;
		//		auxiliar_array_b = list_integer_b->get_data();
		//		array_b_max = auxiliar_array_b->getCapacity();
		//		array_b_quantity = auxiliar_array_b->getQuantity();
		//	}

		//	int a = array_a_max - 1;
		//	for (int b = array_b_max - 1; b >= array_b_max - array_b_quantity; a--, b--) {
		//		std::string num_a = std::to_string(*(auxiliar_array_a)[a]);
		//		std::string num_b = std::to_string(*(*auxiliar_array_b)[b]);
		//		int digit_a = 0;
		//		int digit_b = 0;
		//		std::string subtraction;
		//		int a_digit_index = num_a.length() - 1;
		//		int b_digit_index = num_b.length() - 1;
		//		while (a_digit_index >= 0 || b_digit_index >= 0) {

		//			
		//			if (a_digit_index < 0) {
		//				//Negative
		//				integer_subtraction->add_digits(stoi(num_b.substr(0, b_digit_index)));
		//			}
		//			else if(b_digit_index < 0){
		//				//Positive
		//				std::cout << a_digit_index;
		//				subtraction = ((a_digit_index == 0) ? std::string(1, (num_a[0])) : num_a.substr(0, a_digit_index)) + subtraction;
		//				//integer_subtraction->add_digits((a_digit_index == 0 ? (int)num_a[0] - '0' : stoi(num_a.substr(0, a_digit_index))));
		//			}
		//			else {
		//				digit_a = (int)num_a[a_digit_index] - '0';
		//				digit_b = (int)num_b[b_digit_index] - '0';

		//				if (digit_a >= digit_b) {
		//					int resta = digit_a - digit_b;
		//					subtraction = std::to_string(resta) + subtraction;

		//				}
		//				else if (list_integer_a->get_previous()) {
		//					bool k = true;
		//					NodoDoble<Array>* aux = list_integer_a;
		//					std::string num_a_auxiliar = num_a;
		//					int a = a_digit_index - 1;
		//					while (k) { //List 
		//						Array auxiliar_number(*(aux->get_data()));
		//						int auxiliar_number_index = auxiliar_number.getCapacity() - 1;
		//						while (auxiliar_number_index >= 0) { //Array
		//							num_a_auxiliar = *(*aux->get_data())[auxiliar_number_index];
		//							while (a >= 0) { // Number
		//								if ((int)num_a_auxiliar[a] - '0' > 0) {
		//									num_a_auxiliar[a] = (((int)(num_a_auxiliar[a] - '0')) - 1) + '0';
		//									aux->get_data()->interchange(new int(stoi(num_a_auxiliar)), auxiliar_number_index);
		//									digit_a += 10;
		//									subtraction = std::to_string(digit_a - digit_b) + subtraction;
		//									k = false;
		//									break;
		//								}
		//								a--;
		//							}
		//							aux = aux->get_previous();
		//							if (aux == nullptr) {
		//								k = false;
		//							}
		//							else {
		//								a = aux->get_data()->getCapacity() - 1;
		//							}
		//						}
		//					}


		//				}
		//				else if (auxiliar_array_a[a - 1]) {

		//				}
		//				else if (list_integer_a->get_previous()) {

		//				}
		//			}
		//			
		//			

		//			a_digit_index--;
		//			b_digit_index--;
		//		}

		//		//for (int a = num_a.length() - 1; a >= 0; a--) {
		//		//	digit_a = (int)num_a[a] - '0';
		//		//	for (int b = num_a.length() - 1; b >= 0; b--) {
		//		//		digit_b = (int)num_a[b] - '0';
		//		//		if (digit_a >= digit_b) {
		//		//			int resta = digit_a - digit_b;
		//		//			subtraction = std::to_string(resta) + subtraction;
		//		//		}
		//		//		else if (a - 1 >= 0) { //There are more digits 

		//		//			int a = num_a.length() - 1 - a;
		//		//			while (a >= 0) {
		//		//				if ((int) num_a[a] - '0' > 0) {
		//		//					num_a[a] = (((int)(num_a[a] - '0')) - 1) + '0';
		//		//					digit_a += 10;
		//		//					subtraction = std::to_string(digit_a - digit_b) + subtraction;
		//		//					break;
		//		//				}
		//		//				a--;
		//		//			}
		//		//			
		//		//			//NodoDoble<Array>* aux_node = list_integer_a->get_previous();
		//		//			//int a = a - 1;

		//		//			//while (*(auxiliar_array_a)[a] <= 0) {
		//		//			//	a--;
		//		//			//	if (a < 0) {
		//		//			//		aux_node = aux_node->get_previous();
		//		//			//		a = aux_node->get_data()->getCapacity();
		//		//			//	}
		//		//			//}

		//		//			//auxiliar_array_a.interchange(new int(*(auxiliar_array_a)[a] - 1), a);


		//		//		}
		//		//		else if(auxiliar_array_a[a - 1]){ //There are more cells
		//		//		}
		//		//		else if(list_integer_a->get_previous()){

		//		//		}
		//		//		else { //Negative
		//		//			subtraction += std::to_string(digit_a - digit_b);
		//		//		}
		//		//		

		//		//	}
		//		//}
		//		if (subtraction_array == nullptr) {
		//			subtraction_array = new Array;
		//			subtraction_array->add(new int(std::stoi(subtraction)));
		//			prepend(subtraction_array, integer_subtraction->integer);
		//		}
		//		else {

		//			integer_subtraction->add_digits(std::stoi(subtraction));

		//		}

		//	//	if ((auxiliar_array_a)[a]) {
		//	//		if (*(auxiliar_array_a)[a] >= *(*auxiliar_array_b)[b]) {
		//	//			auxiliar_subtraction = (std::to_string(*(auxiliar_array_a)[a] - *(*auxiliar_array_b)[b]));
		//	//			if (subtraction_array == nullptr) {
		//	//				subtraction_array = new Array;
		//	//				subtraction_array->add(new int(std::stoi(auxiliar_subtraction)));
		//	//				prepend(subtraction_array, integer_subtraction->integer);
		//	//			}
		//	//			else {

		//	//				integer_subtraction->add_digits(std::stoi(auxiliar_subtraction));

		//	//			}
		//	//		}
		//	//		else { // Borrow or negative
		//	//			NodoDoble<Array>* aux_node = list_integer_a;
		//	//			
		//	//			while (aux_node || ) {

		//	//			}

		//	//		}

		//	//	}

		//	//}
		//	//if ((auxiliar_array_a)[a] && (*(auxiliar_array_a)[a]) != 0) {

		//	//	for (int a_aux = a; a_aux >= array_a_max - array_a_quantity; a_aux--) {
		//	//		integer_subtraction->add_digits(*(auxiliar_array_a)[a_aux]);
		//	//	}

		//	}
		//	if (list_integer_a) {
		//		list_integer_a = list_integer_a->get_previous();
		//	}
		//	if (list_integer_b) {
		//		list_integer_b = list_integer_b->get_previous();
		//	}
		//}


		return *integer_subtraction;

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
	catch (int) {

	}
}
//Integer& Integer::operator*(const Integer& integer_b)
//{
//	bool add_carry = false;
//	bool prev = false;
//	int zeros = 1;
//	//int size_a = elements(this->integer);
//	//int size_b = elements(integer_b.getInteger());
//
//	//try {
//	//	if (size_a == 0 || size_b == 0) {
//	//		throw 0;
//	//	}
//
//	//	Array* auxiliar_array_a = nullptr;
//	//	Array* auxiliar_array_b = nullptr;
//	//	NodoDoble<Array>* list_integer_a = nullptr;
//	//	NodoDoble<Array>* list_integer_b = nullptr;
//
//	//	if (*this > integer_b) {
//	//		// this
//	//		list_integer_a = last(this->integer);
//
//	//		// integer_b
//	//		list_integer_b = last(integer_b.integer);
//	//	}
//	//	else {
//	//		// this
//	//		list_integer_b = last(this->integer);
//
//	//		// integer_b
//	//		list_integer_a = last(integer_b.integer);
//	//	}
//
//
//
//	//	// New Integer
//	//	// *this + integer_b
//	//	Array* multiplication_array = nullptr;
//	//	Integer* integer_multiplication = new Integer();
//
//	//	int carry = 0;
//
//
//	//	while (list_integer_a != nullptr &&  list_integer_b != nullptr) {
//
//	//		auxiliar_array_b = list_integer_b->get_data();
//
//	//		//integer_b, cell b
//	//		for (int b = auxiliar_array_b->getCapacity() - auxiliar_array_b->getQuantity(); b >= 0; b--) {
//
//	//			int digit = ((*auxiliar_array_a)[b] ? (*(*auxiliar_array_a)[b]) % 10 : throw 0);
//
//
//
//	//		}
//
//	//	}
//
//
//	//}
//	//catch (int) {
//	//	// At least one of the Integer is empty
//	//}
//
//	//int size_a = elements(this->integer);
//	//int size_b = elements(integer_b.getInteger());
//
//	//try {
//	//	if (size_a == 0 || size_b == 0) {
//	//		throw 0;
//	//	}
//
//	//	Array* auxiliar_array_a = nullptr;
//	//	Array* auxiliar_array_b = nullptr;
//	//	NodoDoble<Array>* list_integer_a = nullptr;
//	//	NodoDoble<Array>* list_integer_b = nullptr;
//
//	//	if (*this > integer_b) {
//	//		// this
//	//		list_integer_a = last(this->integer);
//
//	//		// integer_b
//	//		list_integer_b = last(integer_b.integer);
//	//	}
//	//	else {
//	//		// this
//	//		list_integer_b = last(this->integer);
//
//	//		// integer_b
//	//		list_integer_a = last(integer_b.integer);
//	//	}
//
//	int size_a = elements(this->integer);
//	int size_b = elements(integer_b.getInteger());
//	try {
//		if (size_a == 0 || size_b == 0) {
//			throw 0;
//		}
//
//		if (*this == ZERO || integer_b == ZERO) {
//			return (*new Integer(ZERO));
//		}
//
//		Array* auxiliar_array_a = nullptr;
//		Array* auxiliar_array_b = nullptr;
//		NodoDoble<Array>* list_integer_a = nullptr;
//		NodoDoble<Array>* list_integer_a_aux = nullptr;
//		NodoDoble<Array>* list_integer_b = nullptr;
//		if (*this > integer_b) {
//			// this
//			list_integer_a = last(this->integer);
//
//			// integer_b
//			list_integer_b = last(integer_b.integer);
//		}
//		else {
//			// this
//			list_integer_b = last(this->integer);
//
//			// integer_b
//			list_integer_a = last(integer_b.integer);
//		}
//
//		// New Integer
//		// *this * integer_b
//		Array* multiplication_array = nullptr;
//		Integer* integer_multiplication = new Integer();
//
//		//The addition auxiliar array
//
//		Integer addition_aux;
//
//		int carry = 0;
//		int shift = 0;
//
//		/*
//		Lists
//		*/
//		// integer_b
//		int b_digit = 0;
//		while (list_integer_b != nullptr) {
//			auxiliar_array_b = list_integer_b->get_data();
//			for (int b = auxiliar_array_b->getCapacity() - 1; b >= auxiliar_array_b->f_index(); b--) { // B array
//				int num = *(*auxiliar_array_b)[b];
//				int pw = 0;
//				while (num > 0) {
//					b_digit = num % 10;
//					num /= 10;
//
//					//Add the shifts
//					std::string shift_len(shift,'0');
//					
//					list_integer_a_aux = list_integer_a;
//					while (list_integer_a_aux) { // integer_a
//						auxiliar_array_a = list_integer_a_aux->get_data();
//						for (int a = auxiliar_array_a->getCapacity() - 1; a >= auxiliar_array_a->f_index() || carry; a--) { // A array
//							long long cast_mult = 0;
//							if (!(*auxiliar_array_a)[a] && carry) {
//								cast_mult = carry;
//								carry = 0;
//							}
//							else {
//
//
//								cast_mult = (long long)b_digit * (long long) * (*auxiliar_array_a)[a] + carry;
//								carry = 0;
//								if (digits_primitive(cast_mult) < MAX_DIGITS && ((*auxiliar_array_a)[a - 1] || (list_integer_a_aux->get_previous()))) {
//									zeros = pow(10, MAX_DIGITS - digits_primitive(cast_mult));
//								}
//								if (std::to_string(cast_mult).length() > MAX_DIGITS) { //Carry
//									int pw = pow(10, (digits_primitive(cast_mult) - 1));
//									carry = cast_mult / pw;
//									//cast_mult = std::stoll(std::to_string(cast_mult).substr(1, std::to_string(cast_mult).length()));
//									long long aa = 1;
//									long long aux_cast = cast_mult;
//									cast_mult = 0;
//									while (aa < pw) {
//										cast_mult += (aux_cast % 10) * aa;
//										aux_cast /= 10;
//										aa *= 10;
//									}
//									if (digits_primitive(cast_mult) < MAX_DIGITS && carry) {
//										add_carry = true;
//									}
//								}
//
//							}
//
//							//addition_aux = parse("9" + shift_len);
//
//							if (add_carry && prev) {
//								addition_aux.add_digits(cast_mult);
//								add_carry = false;
//								prev = false;
//							}
//							else if (cast_mult == 0) {
//								shift_len += std::string(MAX_DIGITS, '0');
//							}
//							else if (!shift_len.empty()) {
//								int find_not_zero = cast_mult;
//								while (find_not_zero % 10 == 0) {
//									shift_len += "0";
//									find_not_zero /= 10;
//								}
//								cast_mult = find_not_zero;
//								shift_len = std::to_string(cast_mult % 10) + shift_len;
//								addition_aux = parse(shift_len);
//								cast_mult /= 10;
//								shift_len = "";
//								addition_aux.add_one_by_one(cast_mult);
//							}
//							else if (b_digit == 0 && (*auxiliar_array_a)[a]) {
//								addition_aux.add_digits(cast_mult);
//							}
//							else {
//								addition_aux.add_one_by_one(cast_mult);
//							}
//
//							if (add_carry && !prev) {
//								prev = true;
//							}
//
//
//						}
//						list_integer_a_aux = list_integer_a_aux->get_previous();
//					}
//					std::cout << "\nNumero: " << addition_aux;
//					if (!integer_multiplication->integer) {
//						*integer_multiplication = addition_aux;
//					}
//					else {
//						*integer_multiplication += addition_aux;
//					}
//					addition_aux.clear_integer();
//					std::cout << "\nSumatoria: " << *integer_multiplication;
//
//					shift++;
//				}
//				//int w = pow(10, auxiliar_array_b->getCapacity() - (b + 1));
//				//b_digit = (*(*auxiliar_array_b)[b] / w) % (10 * auxiliar_array_b->getCapacity() - b);
//
//			
//			}
//
//			list_integer_b = list_integer_b->get_previous();
//		}
//
//		//while (list_integer_a != nullptr && list_integer_b != nullptr) {
//
//		//	/*
//		//	Arrays
//		//	*/
//		//	auxiliar_array_a = list_integer_a->get_data();
//		//	auxiliar_array_b = list_integer_b->get_data();
//		//	array_a_max = auxiliar_array_a->getCapacity();
//		//	array_a_quantity = auxiliar_array_a->getQuantity();
//		//	array_b_max = auxiliar_array_b->getCapacity();
//		//	array_b_quantity = auxiliar_array_b->getQuantity();
//		//	//---
//
//
//
//
//		//	//int b = auxiliar_array_b->getCapacity() - 1;
//		//	
//		//	////integer_b
//		//	//for (int b = auxiliar_array_b->getCapacity() - 1; b>=array_b_max - array_b_quantity; b--) {
//
//		//	//	//integer_a
//		//	//	for (int a = auxiliar_array_a->getCapacity() - 1; (a >= array_a_max - array_a_quantity) || carry; a--) {
//		//	//		std::string auxiliar_multiplication;
//		//	//		if (carry && (*auxiliar_array_a)[a]) {
//		//	//			long long cast_a = (long long) *(*auxiliar_array_a)[a];
//		//	//			long long cast_b = (long long) *(*auxiliar_array_b)[b];
//		//	//			long long multiplication = cast_a * cast_b + carry;
//		//	//			auxiliar_multiplication = (std::to_string(multiplication));
//		//	//			carry = 0;
//		//	//			if (auxiliar_multiplication.length() > MAX_DIGITS) {
//		//	//				carry = atoi(auxiliar_multiplication.substr(0, auxiliar_multiplication.length() - MAX_DIGITS).c_str());
//		//	//				auxiliar_multiplication = auxiliar_multiplication.substr(auxiliar_multiplication.length() - MAX_DIGITS, auxiliar_multiplication.length());
//		//	//			}
//		//	//			if (multiplication_array == nullptr) {
//		//	//				multiplication_array = new Array;
//		//	//				multiplication_array->add(new int(std::stoi(auxiliar_multiplication)));
//		//	//				prepend(multiplication_array, integer_multiplication->integer);
//		//	//			}
//		//	//			else {
//
//		//	//				integer_multiplication->add_digits(std::stoi(auxiliar_multiplication));
//
//		//	//			}
//		//	//		}
//		//	//		else {
//		//	//			if ((*auxiliar_array_b)[a]) {
//		//	//				long long cast_a = (long long) *(*auxiliar_array_a)[a];
//		//	//				long long cast_b = (long long) *(*auxiliar_array_b)[b];
//		//	//				long long multiplication = cast_a * cast_b + carry;
//		//	//				auxiliar_multiplication = (std::to_string(multiplication));
//		//	//				carry = 0;
//
//		//	//				if (auxiliar_multiplication.length() > MAX_DIGITS) {
//		//	//					carry = atoi(auxiliar_multiplication.substr(0, auxiliar_multiplication.length() - MAX_DIGITS).c_str());
//		//	//					auxiliar_multiplication = auxiliar_multiplication.substr(auxiliar_multiplication.length() - MAX_DIGITS, auxiliar_multiplication.length());
//		//	//				}
//
//
//		//	//				if (multiplication_array == nullptr) {
//		//	//					multiplication_array = new Array;
//		//	//					multiplication_array->add(new int(std::stoi(auxiliar_multiplication)));
//		//	//					prepend(multiplication_array, integer_multiplication->integer);
//		//	//				}
//		//	//				else {
//
//		//	//					integer_multiplication->add_digits(std::stoi(auxiliar_multiplication));
//
//		//	//				}
//		//	//			}
//		//	//			else {
//		//	//				if (carry) {
//
//		//	//					auxiliar_multiplication = ((*auxiliar_array_a)[a] ? (std::to_string(*(*auxiliar_array_a)[a] + carry)) : std::to_string(carry));
//		//	//					carry = 0;
//		//	//					if (auxiliar_multiplication.length() > MAX_DIGITS) {
//		//	//						carry = (int)auxiliar_multiplication[0] - '0';
//		//	//						auxiliar_multiplication = auxiliar_multiplication.substr(1, auxiliar_multiplication.length() - 1);
//		//	//					}
//		//	//					integer_multiplication->add_digits(stoi(auxiliar_multiplication));
//		//	//				}
//		//	//				else {
//		//	//					integer_multiplication->add_digits(*(*auxiliar_array_a)[a]);
//		//	//				}
//		//	//			}
//
//		//	//		}
//		//	//	}
//		//	//}
//		//	list_integer_a = list_integer_a->get_previous();
//		//	list_integer_b = list_integer_b->get_previous();
//
//		//}
//
//
//		return *integer_multiplication;
//
//	}
//	catch (int) {
//		// At least one of the Integer is empty
//	}
//
//	//int size_a = elements(this->integer);
//	//int size_b = elements(integer_b.getInteger());
//
//	//try {
//	//	if (size_a == 0 || size_b == 0) {
//	//		throw 0;
//	//	}
//
//	//	Array* auxiliar_array_a = nullptr;
//	//	Array* auxiliar_array_b = nullptr;
//	//	NodoDoble<Array>* list_integer_a = nullptr;
//	//	NodoDoble<Array>* list_integer_b = nullptr;
//
//	//	if (*this > integer_b) {
//	//		// this
//	//		list_integer_a = last(this->integer);
//
//	//		// integer_b
//	//		list_integer_b = last(integer_b.integer);
//	//	}
//	//	else {
//	//		// this
//	//		list_integer_b = last(this->integer);
//
//	//		// integer_b
//	//		list_integer_a = last(integer_b.integer);
//	//	}
//
//
//
//	//	// New Integer
//	//	// *this + integer_b
//	//	Array* multiplication_array = nullptr;
//	//	Integer* integer_multiplication = new Integer();
//
//	//	int carry = 0;
//
//	//	int array_a_max = 0;
//	//	int array_b_max = 0;
//	//	int array_a_quantity = 0;
//	//	int array_b_quantity = 0;
//	//	/*
//	//	Lists
//	//	*/
//	//	while (list_integer_a != nullptr && list_integer_b != nullptr) {
//
//	//		/*
//	//		Arrays
//	//		*/
//	//		auxiliar_array_a = list_integer_a->get_data();
//	//		auxiliar_array_b = list_integer_b->get_data();
//	//		array_a_max = auxiliar_array_a->getCapacity();
//	//		array_a_quantity = auxiliar_array_a->getQuantity();
//	//		array_b_max = auxiliar_array_b->getCapacity();
//	//		array_b_quantity = auxiliar_array_b->getQuantity();
//	//		int b = auxiliar_array_b->getCapacity() - 1;
//	//		for (int a = auxiliar_array_a->getCapacity() - 1; (a >= array_a_max - array_a_quantity) || carry; a--) { //Si hay acarreo no puede detenerse la suma
//
//	//			std::string auxiliar_multiplication;
//	//			if ((*auxiliar_array_b)[b]) {
//	//				long long cast_a = (long long) *(*auxiliar_array_a)[a];
//	//				long long cast_b = (long long) *(*auxiliar_array_b)[b];
//	//				long long multiplication = cast_a * cast_b + carry;
//	//				auxiliar_multiplication = (std::to_string(multiplication));
//	//				carry = 0;
//
//	//				if (auxiliar_multiplication.length() > MAX_DIGITS) { 
//	//					carry = atoi(auxiliar_multiplication.substr(0, auxiliar_multiplication.length() - MAX_DIGITS).c_str());
//	//					auxiliar_multiplication = auxiliar_multiplication.substr(auxiliar_multiplication.length() - MAX_DIGITS, auxiliar_multiplication.length());
//	//				}
//
//
//	//				if (multiplication_array == nullptr) {
//	//					multiplication_array = new Array;
//	//					multiplication_array->add(new int(std::stoi(auxiliar_multiplication)));
//	//					prepend(multiplication_array, integer_multiplication->integer);
//	//				}
//	//				else {
//
//	//					integer_multiplication->add_digits(std::stoi(auxiliar_multiplication));
//
//	//				}
//	//			}
//	//			else {
//	//				if (carry) {
//
//	//					auxiliar_multiplication = ((*auxiliar_array_a)[a] ? (std::to_string(*(*auxiliar_array_a)[a] + carry)) : std::to_string(carry));
//	//					carry = 0;
//	//					if (auxiliar_multiplication.length() > MAX_DIGITS) {
//	//						carry = (int)auxiliar_multiplication[0] - '0';
//	//						auxiliar_multiplication = auxiliar_multiplication.substr(1, auxiliar_multiplication.length() - 1);
//	//					}
//	//					integer_multiplication->add_digits(stoi(auxiliar_multiplication));
//	//				}
//	//				else {
//	//					integer_multiplication->add_digits(*(*auxiliar_array_a)[a]);
//	//				}
//	//				//return *integer_addition;
//	//			}
//
//
//	//			b--;
//
//
//	//		}
//
//	//		list_integer_a = list_integer_a->get_previous();
//	//		list_integer_b = list_integer_b->get_previous();
//
//	//	}
//
//
//	//	return *integer_multiplication;
//
//	//}
//	//catch (int) {
//	//	// At least one of the Integer is empty
//	//}
//
//}
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
			throw 0;
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
	catch (int) {
		//At least one of the Integer is empty
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
	catch (int) {
		//At least one of the Integer is empty
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
	return !(*this == integer_b);
}

std::string Integer::toString()
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
			throw 0;
		}

		//if (integer_b == ZERO && (*(*(*this->integer)->get_data())[(*this->integer)->get_data()->f_index()] > 0 || (*(*(*this->integer)->get_data())[(*this->integer)->get_data()->f_index()] == 0 && ((*this->integer)->get_next() != nullptr || (*this->integer)->get_data()->f_index() < MAX_TAM - 1)))) {
		//	return false;
		//}
		//else if (*this == ZERO && (*(*(*integer_b.integer)->get_data())[(*integer_b.integer)->get_data()->f_index()] > 0 || (*(*(*integer_b.integer)->get_data())[(*integer_b.integer)->get_data()->f_index()] == 0 && ((*integer_b.integer)->get_next() != nullptr || (*integer_b.integer)->get_data()->f_index() < MAX_TAM - 1)))) {
		//	return true;
		//}

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
		else if (this->digits() > integer_b.digits()) {
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
		//NodoDoble<Array>* aux = *integer.integer;
		//while (aux) {
		//	output << *aux->get_data();
		//	aux = aux->get_next();
		//}
		//return output;
	}
	catch (int) {
		// Integer is empty
	}
}
