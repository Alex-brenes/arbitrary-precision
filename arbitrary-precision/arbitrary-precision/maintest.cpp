#include <iostream>
#include "integer.h"

int main() {


	Integer entero_a;
	entero_a = Integer::parse("10");
	Integer entero_b(10);
	Integer entero_c = entero_a + entero_b;
	std::cout << entero_c;
	return 0;
}