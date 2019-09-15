#include <iostream>
#include "integer.h"

int main() {
	Integer entero_a(Integer::parse("111111111222222222333333333444444444555555555666666666777777777888888888999999999"));
	Integer entero_b;
	Integer entero_c;
	Integer entero_d(entero_a);
	Integer entero_e = Integer::parse("999999999");
	Integer entero_f = Integer::parse("999999999999999999");
	entero_b = Integer::parse("111111111222222222333333333444444444555555555666666666777777777888888888999999999"); entero_c = Integer::parse("96548966669");
	//long long b(111111111);
	//std::string a = std::to_string(b);
	//std::cout << entero_b + entero_a;
	//std::cout << a;
	//entero_e += entero_f;
	std::cout << entero_b + entero_a;
	//std::cout << i<<std::endl;
	//std::cout << entero_e;
	//std::cout<< Integer::parse("111111111222222222333333333444444444555555555666666666777777777888888888999999999");
	//std::cout << std::endl<<std::endl << entero_d << std::endl << std::endl << std::endl;
	//std::cout << entero_c << std::endl << std::endl << std::endl;
	//std::cout << entero_d << std::endl << std::endl << std::endl;
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