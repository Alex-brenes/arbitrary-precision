#ifndef LISTA_SIMPLE_H
#define LISTA_SIMPLE_H
template<typename T>
struct NodoSimple {
private:
	T* data;
	struct NodoSimple<T>* next;
public:
	T* get_data() { return data; }
	void set_data(T* dta) { data = dta; }
	NodoSimple<T>* get_next() { return next; }
	void set_next(NodoSimple<T>* nxt) { next = nxt; }
};

template<typename T>
bool empty(NodoSimple<T>** head) {
	if (!head)
		return true;
	return !(*head);
}

template <typename T>
int elements(NodoSimple<T>** head) {
	int counter = 0;
	if (!empty(head)) {
		NodoSimple<T>* aux = *head;
		while (aux != nullptr) {
			counter++;
			aux = aux->get_next();
		}
	}
	return counter;
}

template <typename T>
void prepend(T* new_data,NodoSimple<T>**& head) {
	struct NodoSimple<T>* nuevo_nodo = new struct NodoSimple<T>;
	nuevo_nodo->set_data(new_data);
	nuevo_nodo->set_next(nullptr);

	if (!head) {
		head = new struct NodoSimple<T>*;
		*head = nuevo_nodo;
	}
	else {
		if (!(*head)) {
			*head = nuevo_nodo;
		}
		else {
			nuevo_nodo->set_next(*head);
			*head = nuevo_nodo;
		}
	}

}

template<typename T>
size_t find_pos(NodoSimple<T>** head,T& element) {
	NodoSimple<T>* aux = *head;
	int pos = 0;
	while (aux) {
		if (element == *(aux->get_data()))
			return pos;
		pos++;
		aux = aux->get_next();
	}
	return -1;
}

template<typename T>
T* find(NodoSimple<T>** head, T& element) {
	NodoSimple<T>* aux = *head;
	while (aux) {
		if (element == *(aux->get_data()))
			return aux->get_data();
		aux = aux->get_next();
	}
	return nullptr;
}


template<typename T>
void append(T* new_data,NodoSimple<T>**& head) {
	struct NodoSimple<T>* nuevo_nodo = new struct NodoSimple<T>;
	nuevo_nodo->set_data(new_data);
	nuevo_nodo->set_next(nullptr);
	if (!head) {
		head = new struct NodoSimple<T>*;
		*head = nuevo_nodo;
	}
	else {
		if (!(*head)) {
			*head = nuevo_nodo;
		}
		else {
			struct NodoSimple<T>* aux = *head;
			while (aux->get_next())
				aux = aux->get_next();
			aux->set_next(nuevo_nodo);
		}
	}
}

template<typename T>
void showList(NodoSimple<T>** head) {
	if (!empty(head)) {
		struct NodoSimple<T>* aux = *head;
		while (aux) {
			std::cout << *aux->get_data() << " ";
			aux = aux->get_next();
		}
	}
	else {
		std::cout << "\nvacia\n";
	}
}
template <typename T>
void clear(NodoSimple<T>** head) {
	if (!empty(head)) {
		NodoSimple<T>* aux;
		while (!empty(head)) {
			aux = (*head)->get_next();
			delete (*head);
			*head = aux;
		}
		delete (*head);
	}
}
template <typename T>
T* sacar_primero(NodoSimple<T>** head) {
	if (empty(head))
		return nullptr;
	NodoSimple<T>* aux = (*head)->get_next();
	T* temp = new T(*((*head)->get_data()));
	delete (*head);
	*head = aux;
	return temp;
}

template <typename T>
T* sacar_ultimo(NodoSimple<T>** head) {
	if (empty(head))
		return nullptr;
	NodoSimple<T>* aux = *head;
	if (!aux->get_next())
		return sacar_primero(head);

	while (aux->get_next()->get_next())
		aux = aux->get_next();
	T* temp = new T(*aux->get_next()->get_data());
	delete aux->get_next();
	aux->set_next(nullptr);
	return temp;
}
template<typename T>
T* sacar(NodoSimple<T>** head,T& element) {
	if (empty(head))
		return nullptr;
	
	NodoSimple<T>* aux = *head;
	NodoSimple<T>* prev = *head;
	while (aux && element != *aux->get_data()) {
		prev = aux;
		aux = aux->get_next();
	}

	if (aux) {
		T* aux2 = new T(*aux->get_data());
		prev->set_next(aux->get_next());
		delete aux;
		return aux2;
	}
	else {
		return nullptr;
	}
}
#endif // !LISTA_SIMPLE_H