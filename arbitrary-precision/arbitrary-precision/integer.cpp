#include "integer.h"

Integer::Integer(int n) {
	Array* arreglo = new Array;
	arreglo->agregar(new int(n));
	append(arreglo, this->integer);
}

NodoDoble<Array>** Integer::getInteger() const
{
	return this->integer;
}

Integer::~Integer()
{
	clear(integer);
	delete integer;
}

std::ostream& operator<<(std::ostream& output, const Integer& integer)
{
	NodoDoble<Array>* aux = *(integer.getInteger());
	while (aux != nullptr) {
		output << *(aux->get_data());
		aux = aux->get_next();
	}
	return output;
}
