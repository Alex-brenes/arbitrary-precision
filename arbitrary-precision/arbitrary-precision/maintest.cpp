#include <iostream>
#include "integer.h"

int main() {
	Integer entero_a(Integer::parse("111111111222222222333333333444444444555555555666666666777777777888888888999999999"));
	Integer entero_b;
	Integer entero_c;
	Integer entero_d(entero_a);
	Integer entero_e = Integer::parse("123123123");
	Integer entero_f = Integer::parse("123123123123123123");
	entero_b = Integer::parse("111111111222222222333333333444444444555555555666666666777777777888888888999999999"); 
	std::cout << entero_e - entero_f;

	return 0;
}