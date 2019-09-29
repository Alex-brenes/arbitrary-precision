#include <iostream>
#include <chrono>
#include "integer.h"
Integer& fibonacci(Integer);
Integer& factorial(Integer);
int main() {
	Integer entero_a(Integer::parse("123123123123123123123123132123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123123"));
	Integer entero_c(Integer::parse("12312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312312123123123"));
	Integer entero_d(entero_a);

	//std::cout << "\n" << entero_a + entero_c;
	auto start = std::chrono::system_clock::now();
	std::cout << fibonacci(10000);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<float, std::milli> duration = end - start;

	std::cout << "\nDuration: " << duration.count() * std::chrono::milliseconds::period::num / std::chrono::milliseconds::period::den << std::endl;
		return 0;
}

Integer& factorial(Integer integer) {
	Integer *fact= new Integer(1);
	Integer i(1);
	while (i <= integer) {
		std::cout << "\n--------" << i<<"\n";
		if (i==Integer(93)) {
			std::cout << "";
		}
		*fact *= i;
		i++;
	}
	return *fact;
}

Integer& fibonacci(Integer a) {
	Integer x = Integer::ZERO;
	Integer y = Integer::ONE;
	Integer z = Integer::ZERO;
	for (Integer i = Integer::ZERO; i < a; i++) {
		//std::cout << i<<"\n";
		z = x + y;
		x = y;
		y = z;
		//std::cout << i;
	}
	Integer* r = new Integer(x);
	return *r;
}
