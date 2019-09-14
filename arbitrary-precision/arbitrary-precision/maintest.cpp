#include <iostream>
#include "integer.h"

int main() {


	Integer entero_a;
	entero_a = Integer::parse("-1111111111222222222333333333444444444555555555666666666777777777888888888999999999");
	//entero_a = Integer::parse("50");
	std::cout << entero_a;
	return 0;
}