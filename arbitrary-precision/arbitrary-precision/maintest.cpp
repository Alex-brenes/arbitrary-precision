#include <iostream>
#include "integer.h"

int main() {


	Integer entero_a;
	Integer entero_b;
	entero_a = Integer::parse("111111111222222222333333333444444444555555555666666666777777777888888888999999999111111111222222222333333333444444444555555555666666666777777777888888888999999999111111111222222222333333333444444444555555555666666666777777777888888888999999999");
	entero_b = Integer::parse("60");
	Integer entero_c(entero_a);
	//entero_a = Integer::parse("50");
	Array a;

	a.agregar(new int(888888888));
	a.agregar(new int(777777777));
	a.agregar(new int(666666666));
	a.agregar(new int(555555555));
	a.agregar(new int(444444444));
	a.agregar(new int(333333333));
	a.agregar(new int(222222222));
	a.agregar(new int(111111111));
	std::cout << a << std::endl;
	Array b(a);
	std::cout << b << std::endl;
	std::cout << entero_c << std::endl;
	std::cout << entero_a;
	return 0;
}