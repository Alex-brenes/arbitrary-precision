#include <iostream>
#include "integer.h"
void fibonacci(Integer&);
int main() {
	Integer entero_a(Integer::parse("111111111222222222333333333444444444555555555666666666777777777888888888999999999"));
	Integer entero_b;
	Integer entero_c;
	Integer entero_d(entero_a);
	Integer entero_e = Integer::parse("64165498441654");
	Integer entero_f = Integer::parse("0");
	//std::cout << std::stoi("0001");
	
	std::cout << "\n"<<entero_e * entero_f;
		return 0;
}

Integer& fibonacci(Integer a) {
	Integer* i = nullptr;
	std::stringstream s;
	while (a > Integer::ZERO) {


		s << "";

		a -= Integer::ONE;
	}
	*i = Integer::parse(s.str());
	return *i;
}
