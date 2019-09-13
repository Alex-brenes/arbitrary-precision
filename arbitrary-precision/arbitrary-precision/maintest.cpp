#include <iostream>
#include "integer.h"

int main() {


	Integer* b = new Integer();
	Integer* a = new Integer(100);
	Integer* c = new Integer();

	*b = Integer::parse("1111111113333333339999999998888888887777777766688854654216857875665649744");

	
	
	std::cout << *b << std::endl;
	std::cout << *b << std::endl;
	std::cout << (*a > *b ? "true" : "false");
	
	delete b;
	delete a;
	return 0;
}