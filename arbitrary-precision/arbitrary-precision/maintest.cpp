#include <iostream>
#include "integer.h"

int main() {


	Integer* b = new Integer();
	*b = Integer::parse("112233445566778899001122334");
	std::cout << *b;

	delete b;
	return 0;
}