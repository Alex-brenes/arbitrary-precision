#include "integer.h"

void Integer::add_digits(int digit) {
	//Head array
	Array * arr = (*this->integer)->get_data();
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
	arr->add(new int(n));
	prepend(arr, this->integer);
}

Integer::Integer(long n) {
	Array* arr = new Array;
	arr->add(new int(n));
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
						addition_array->add(new int(std::stoi(auxiliar_addition)));
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
Integer& Integer::operator-(const Integer& integer_b)
{

	int size_a = elements(this->integer);
	int size_b = elements(integer_b.getInteger());

	try {
		if (size_a == 0 || size_b == 0) {
			throw 0;
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
		
		if (list_integer_a_prev != nullptr && list_integer_b == nullptr) { // Positive
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
			std::cout << "";
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
	//int size_a = elements(this->integer);
	//int size_b = elements(integer_b.getInteger());

	//try {
	//	if (size_a == 0 || size_b == 0) {
	//		throw 0;
	//	}

	//	Array* auxiliar_array_a = nullptr;
	//	Array* auxiliar_array_b = nullptr;
	//	NodoDoble<Array>* list_integer_a = nullptr;
	//	NodoDoble<Array>* list_integer_b = nullptr;

	//	if (*this > integer_b) {
	//		// this
	//		list_integer_a = last(this->integer);

	//		// integer_b
	//		list_integer_b = last(integer_b.integer);
	//	}
	//	else {
	//		// this
	//		list_integer_b = last(this->integer);

	//		// integer_b
	//		list_integer_a = last(integer_b.integer);
	//	}



	//	// New Integer
	//	// *this + integer_b
	//	Array* multiplication_array = nullptr;
	//	Integer* integer_multiplication = new Integer();

	//	int carry = 0;


	//	while (list_integer_a != nullptr &&  list_integer_b != nullptr) {

	//		auxiliar_array_b = list_integer_b->get_data();

	//		//integer_b, cell b
	//		for (int b = auxiliar_array_b->getCapacity() - auxiliar_array_b->getQuantity(); b >= 0; b--) {

	//			int digit = ((*auxiliar_array_a)[b] ? (*(*auxiliar_array_a)[b]) % 10 : throw 0);



	//		}

	//	}


	//}
	//catch (int) {
	//	// At least one of the Integer is empty
	//}

	//int size_a = elements(this->integer);
	//int size_b = elements(integer_b.getInteger());

	//try {
	//	if (size_a == 0 || size_b == 0) {
	//		throw 0;
	//	}

	//	Array* auxiliar_array_a = nullptr;
	//	Array* auxiliar_array_b = nullptr;
	//	NodoDoble<Array>* list_integer_a = nullptr;
	//	NodoDoble<Array>* list_integer_b = nullptr;

	//	if (*this > integer_b) {
	//		// this
	//		list_integer_a = last(this->integer);

	//		// integer_b
	//		list_integer_b = last(integer_b.integer);
	//	}
	//	else {
	//		// this
	//		list_integer_b = last(this->integer);

	//		// integer_b
	//		list_integer_a = last(integer_b.integer);
	//	}

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
			int b = auxiliar_array_b->getCapacity() - 1;
			
			//integer_b
			for (int b = auxiliar_array_b->getCapacity() - 1; b>=array_b_max - array_b_quantity; b--) {

				//integer_a
				for (int a = auxiliar_array_a->getCapacity() - 1; (a >= array_a_max - array_a_quantity) || carry; a--) {
					std::string auxiliar_multiplication;
					if (carry && (*auxiliar_array_a)[a]) {
						long long cast_a = (long long) *(*auxiliar_array_a)[a];
						long long cast_b = (long long) *(*auxiliar_array_b)[b];
						long long multiplication = cast_a * cast_b + carry;
						auxiliar_multiplication = (std::to_string(multiplication));
						carry = 0;
						if (auxiliar_multiplication.length() > MAX_DIGITS) {
							carry = atoi(auxiliar_multiplication.substr(0, auxiliar_multiplication.length() - MAX_DIGITS).c_str());
							auxiliar_multiplication = auxiliar_multiplication.substr(auxiliar_multiplication.length() - MAX_DIGITS, auxiliar_multiplication.length());
						}
						if (multiplication_array == nullptr) {
							multiplication_array = new Array;
							multiplication_array->add(new int(std::stoi(auxiliar_multiplication)));
							prepend(multiplication_array, integer_multiplication->integer);
						}
						else {

							integer_multiplication->add_digits(std::stoi(auxiliar_multiplication));

						}
					}
					else {
						if ((*auxiliar_array_b)[a]) {
							long long cast_a = (long long) *(*auxiliar_array_a)[a];
							long long cast_b = (long long) *(*auxiliar_array_b)[b];
							long long multiplication = cast_a * cast_b + carry;
							auxiliar_multiplication = (std::to_string(multiplication));
							carry = 0;

							if (auxiliar_multiplication.length() > MAX_DIGITS) {
								carry = atoi(auxiliar_multiplication.substr(0, auxiliar_multiplication.length() - MAX_DIGITS).c_str());
								auxiliar_multiplication = auxiliar_multiplication.substr(auxiliar_multiplication.length() - MAX_DIGITS, auxiliar_multiplication.length());
							}


							if (multiplication_array == nullptr) {
								multiplication_array = new Array;
								multiplication_array->add(new int(std::stoi(auxiliar_multiplication)));
								prepend(multiplication_array, integer_multiplication->integer);
							}
							else {

								integer_multiplication->add_digits(std::stoi(auxiliar_multiplication));

							}
						}
						else {
							if (carry) {

								auxiliar_multiplication = ((*auxiliar_array_a)[a] ? (std::to_string(*(*auxiliar_array_a)[a] + carry)) : std::to_string(carry));
								carry = 0;
								if (auxiliar_multiplication.length() > MAX_DIGITS) {
									carry = (int)auxiliar_multiplication[0] - '0';
									auxiliar_multiplication = auxiliar_multiplication.substr(1, auxiliar_multiplication.length() - 1);
								}
								integer_multiplication->add_digits(stoi(auxiliar_multiplication));
							}
							else {
								integer_multiplication->add_digits(*(*auxiliar_array_a)[a]);
							}
						}

					}
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

	//int size_a = elements(this->integer);
	//int size_b = elements(integer_b.getInteger());

	//try {
	//	if (size_a == 0 || size_b == 0) {
	//		throw 0;
	//	}

	//	Array* auxiliar_array_a = nullptr;
	//	Array* auxiliar_array_b = nullptr;
	//	NodoDoble<Array>* list_integer_a = nullptr;
	//	NodoDoble<Array>* list_integer_b = nullptr;

	//	if (*this > integer_b) {
	//		// this
	//		list_integer_a = last(this->integer);

	//		// integer_b
	//		list_integer_b = last(integer_b.integer);
	//	}
	//	else {
	//		// this
	//		list_integer_b = last(this->integer);

	//		// integer_b
	//		list_integer_a = last(integer_b.integer);
	//	}



	//	// New Integer
	//	// *this + integer_b
	//	Array* multiplication_array = nullptr;
	//	Integer* integer_multiplication = new Integer();

	//	int carry = 0;

	//	int array_a_max = 0;
	//	int array_b_max = 0;
	//	int array_a_quantity = 0;
	//	int array_b_quantity = 0;
	//	/*
	//	Lists
	//	*/
	//	while (list_integer_a != nullptr && list_integer_b != nullptr) {

	//		/*
	//		Arrays
	//		*/
	//		auxiliar_array_a = list_integer_a->get_data();
	//		auxiliar_array_b = list_integer_b->get_data();
	//		array_a_max = auxiliar_array_a->getCapacity();
	//		array_a_quantity = auxiliar_array_a->getQuantity();
	//		array_b_max = auxiliar_array_b->getCapacity();
	//		array_b_quantity = auxiliar_array_b->getQuantity();
	//		int b = auxiliar_array_b->getCapacity() - 1;
	//		for (int a = auxiliar_array_a->getCapacity() - 1; (a >= array_a_max - array_a_quantity) || carry; a--) { //Si hay acarreo no puede detenerse la suma

	//			std::string auxiliar_multiplication;
	//			if ((*auxiliar_array_b)[b]) {
	//				long long cast_a = (long long) *(*auxiliar_array_a)[a];
	//				long long cast_b = (long long) *(*auxiliar_array_b)[b];
	//				long long multiplication = cast_a * cast_b + carry;
	//				auxiliar_multiplication = (std::to_string(multiplication));
	//				carry = 0;

	//				if (auxiliar_multiplication.length() > MAX_DIGITS) { 
	//					carry = atoi(auxiliar_multiplication.substr(0, auxiliar_multiplication.length() - MAX_DIGITS).c_str());
	//					auxiliar_multiplication = auxiliar_multiplication.substr(auxiliar_multiplication.length() - MAX_DIGITS, auxiliar_multiplication.length());
	//				}


	//				if (multiplication_array == nullptr) {
	//					multiplication_array = new Array;
	//					multiplication_array->add(new int(std::stoi(auxiliar_multiplication)));
	//					prepend(multiplication_array, integer_multiplication->integer);
	//				}
	//				else {

	//					integer_multiplication->add_digits(std::stoi(auxiliar_multiplication));

	//				}
	//			}
	//			else {
	//				if (carry) {

	//					auxiliar_multiplication = ((*auxiliar_array_a)[a] ? (std::to_string(*(*auxiliar_array_a)[a] + carry)) : std::to_string(carry));
	//					carry = 0;
	//					if (auxiliar_multiplication.length() > MAX_DIGITS) {
	//						carry = (int)auxiliar_multiplication[0] - '0';
	//						auxiliar_multiplication = auxiliar_multiplication.substr(1, auxiliar_multiplication.length() - 1);
	//					}
	//					integer_multiplication->add_digits(stoi(auxiliar_multiplication));
	//				}
	//				else {
	//					integer_multiplication->add_digits(*(*auxiliar_array_a)[a]);
	//				}
	//				//return *integer_addition;
	//			}


	//			b--;


	//		}

	//		list_integer_a = list_integer_a->get_previous();
	//		list_integer_b = list_integer_b->get_previous();

	//	}


	//	return *integer_multiplication;

	//}
	//catch (int) {
	//	// At least one of the Integer is empty
	//}

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
		else if (this->cantidadDigitos() < integer_b.cantidadDigitos()) {
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
				if (number[0] == '0' && aux->get_next()) { 
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
