#include <iostream>
#include "integer.h"

int main() {


	Integer* b = new Integer();
	Integer* a = new Integer(100);
	Integer* c = new Integer();

	*b = Integer::parse("11117777777755555555554645645645645645667788991122334455667788991");

	
	*a = Integer::parse("1111777777775555555555464564564564564566778899112233445566778899");
	std::cout << *a << std::endl;
	std::cout << *b << std::endl;
	std::cout << (*a > *b ? "true" : "false");
	
	delete b;
	delete a;
	return 0;
}