#include <iostream>
#include "integer.h"
Integer& fibonacci(Integer);
Integer& factorial(Integer);
int main() {
	Integer entero_a(Integer::parse("111111111222222222333333333444444444555555555666666666777777777888888888999999999111111111222222222333333333444444444555555555666666666777777777888888888999999999111111111222222222333333333444444444555555555666666666777777777888888888999999999111111111222222222333333333444444444555555555666666666777777777888888888999999999111111111222222222333333333444444444555555555666666666777777777888888888999999999111111111222222222333333333444444444555555555666666666777777777888888888999999999111111111222222222333333333444444444555555555666666666777777777888888888999999999111111111222222222333333333444444444555555555666666666777777777888888888999999999111111111222222222333333333444444444555555555666666666777777777888888888999999999"));
	Integer entero_b;
	Integer entero_c;
	Integer entero_d(entero_a);
	//Integer entero_e = Integer::parse("1307674368000");
	//Integer entero_f = Integer::parse("16");
	//Integer entero_x = Integer::parse("56");
	//Integer entero_y = Integer::parse("12696403353658275925965100847566516959580321051449436762275840000000000000");
	//std::cout <<"\n"<< entero_x * entero_y;
	//std::cout << entero_a;
	Integer aux(93);
	std::cout << "\nFactorial: " << factorial(aux);
	//std::cout << (entero_x < entero_y ? "true" : "false");
		return 0;
}

Integer& factorial(Integer integer) {
	Integer *fact= new Integer(1);
	Integer i(1);
	while (i <= integer) {
		std::cout << "\n--------" << i<<"\n";
		if (i==Integer(93)) {
			std::cout << "";
		}
		*fact *= i;
		i++;
	}
	return *fact;
}

Integer& fibonacci(Integer a) {
	Integer x = Integer::ZERO, y = Integer::ONE, z = Integer::ZERO;
	std::stringstream s;
	for (Integer i = Integer::ZERO; i < a; i++) {
		s<< x;
		z = x + y;
		x = y;
		y = z;
	}
	return Integer::parse(s.str());
}
