#include <iostream>
#include "integer.h"
void fibonacci(Integer&);
int main() {
	Integer entero_a(Integer::parse("111111111222222222333333333444444444555555555666666666777777777888888888999999999"));
	Integer entero_b;
	Integer entero_c;
	Integer entero_d(entero_a);
	Integer entero_e = Integer::parse("1000");
	Integer entero_f = Integer::parse("1");
	Integer entero_x = Integer::parse("-111111111");
	Integer entero_y = Integer::parse("0");
	//std::cout << entero_y;
	Integer aux(100);

	std::cout << (entero_x < entero_y ? "true" : "false");
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
