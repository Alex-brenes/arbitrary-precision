#include <iostream>
#include "integer.h"

int main() {
	Integer* a = new Integer(119832123);
	std::cout << *a;
	delete a;
	std::cin.get();
	return 0;
}