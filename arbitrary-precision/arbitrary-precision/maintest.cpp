//maintest.cpp
//Autores: José Alexander Brenes Brenes; Juan Daniel Quirós
//Funciones de prueba como factorial, fibonacci, y combinaciones para la clase Integer
#include <iostream>
#include <chrono>
#include "integer.h"
Integer& factorial(Integer);
Integer& fibonacci(Integer);
Integer& combinaciones(Integer,Integer);

int main() {
	Integer mil(1000);
	Integer comb_a(350);
	Integer comb_b(500);
	Integer comb_c(650);
	std::cout <<"\n\n\n1000! = "<< factorial(mil);
	std::cout <<"\n\n\nFibonacci(1000) = "<< fibonacci(mil);
	std::cout << "\n\n\nC(1000, 350) = " << combinaciones(mil, comb_a);
	std::cout << "\n\n\nC(1000, 500) = " << combinaciones(mil, comb_b);
	std::cout << "\n\n\nC(1000, 650) = " << combinaciones(mil, comb_c);
	return 0;

}

Integer& factorial(Integer integer) {
	Integer *factorial= new Integer(1);
	Integer i(1);
	while (i <= integer) {
		*factorial *= i;
		i++;
	}
	return *factorial;
}

Integer& fibonacci(Integer a) {
	Integer x = Integer::ZERO;
	Integer y = Integer::ONE;
	Integer z = Integer::ZERO;
	for (Integer i = Integer::ZERO; i < a; i++) {
		z = x + y;
		x = y;
		y = z;
	}
	Integer* fibonacci = new Integer(x);
	return *fibonacci;
}

Integer& combinaciones(Integer n, Integer k) {
	Integer* combinaciones = new Integer;
	*combinaciones = (factorial(n) / (factorial(k) * factorial(n - k)));
	return *combinaciones;
}