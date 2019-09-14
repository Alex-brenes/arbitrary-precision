#include <iostream>
#include "integer.h"

int main() {
	Integer entero_a;
	Integer entero_b;
	Integer entero_c;
	//entero_a = Integer::parse("111111111222222222333333333444444444555555555666666666777777777888888888999999999111111111222222222333333333444444444555555555666666666777777777888888888999999999111111111222222222333333333444444444555555555666666666777777777888888888999999999");
	entero_b = Integer::parse("96549847659");
	entero_a = Integer::parse("96548966669");
	std::cout << entero_a + entero_b;
	//std::cout << entero_a;
	//std::cout << entero_c;
	//std::string i(std::to_string(999999999));
	//std::string o(std::to_string(999999999));
	//std::cout << 999999999 << std::endl;
	//std::cout << (atoi(i.c_str()) + atoi(o.c_str()));
	//std::cout << entero_c << std::endl;
	//std::cout << entero_a;
	return 0;
}