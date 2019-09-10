#ifndef LISTADOBLE_H
#define LISTADOBLE_H

template<typename T>
struct NodoDoble {
private:
	NodoDoble<T>* next;
	NodoDoble<T>* previous;
	T* data;
public:
	T* get_data() { return data; }
	void set_data(T* dta) { data = dta; }
	NodoDoble<T>* get_next() { return next; }
	void set_next(NodoDoble<T>* nxt) { next = nxt; }
	NodoDoble<T>* get_previous() { return previous; }
	void set_prev(NodoDoble<T>* prev) { previous = prev; }
};

template<typename T>
bool empty(NodoDoble<T>** head) {
	if (!head)
		return true;
	return !(*head);
}

template <typename T>
void prepend(T* new_data, NodoDoble<T>**& head) {
	struct NodoDoble<T>* nuevo_nodo = new struct NodoDoble<T>;
	nuevo_nodo->set_data(new_data);
	nuevo_nodo->set_next(nullptr);
	nuevo_nodo->set_prev(nullptr);

	if (!head) {
		head = new struct NodoDoble<T>*;
		*head = nuevo_nodo;
	}
	else {
		if (!(*head)) {
			*head = nuevo_nodo;
		}
		else {
			nuevo_nodo->set_next(*head);
			(*head)->set_prev(nuevo_nodo);
			*head = nuevo_nodo;
		}
	}
}

template<typename T>
size_t find_pos(NodoDoble<T>** head, T& element) {
	NodoDoble<T>* aux = *head;
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
T* find(NodoDoble<T>** head, T& element) {
	NodoDoble<T>* aux = *head;
	while (aux) {
		if (element == *(aux->get_data()))
			return aux->get_data();
		aux = aux->get_next();
	}
	return nullptr;
}


template<typename T>
void append(T* new_data, NodoDoble<T>**& head) {
	struct NodoDoble<T>* nuevo_nodo = new struct NodoDoble<T>;
	nuevo_nodo->set_data(new_data);
	nuevo_nodo->set_next(nullptr);
	nuevo_nodo->set_prev(nullptr);
	if (!head) {
		head = new struct NodoDoble<T>*;
		*head = nuevo_nodo;
	}
	else {
		if (!(*head)) {
			*head = nuevo_nodo;
		}
		else {
			struct NodoDoble<T>* aux = *head;
			while (aux->get_next())
				aux = aux->get_next();
			nuevo_nodo->set_prev(aux);
			aux->set_next(nuevo_nodo);
		}
	}
}

template<typename T>
void showList(NodoDoble<T>** head) {
	if (!empty(head)) {
		struct NodoDoble<T>* aux = *head;
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
void clear(NodoDoble<T>** head) {
	if (!empty(head)) {
		NodoDoble<T>* aux;
		while (!empty(head)) {
			aux = (*head)->get_next();
			delete (*head);
			*head = aux;
		}
		*head = nullptr;
	}
}
template <typename T>
T* sacar_primero(NodoDoble<T>** head) {
	if (empty(head))
		return nullptr;
	NodoDoble<T>* aux = (*head)->get_next();
	T* temp = new T(*((*head)->get_data()));
	aux->set_prev(nullptr);
	delete (*head);
	*head = aux;
	return temp;
}

template <typename T>
void showListReverse(NodoDoble<T>** head) {
	if (!empty(head)) {
		struct NodoDoble<T>* aux = *head;
		while (aux->get_next())
			aux = aux->get_next();
		while (aux){
			std::cout << *aux->get_data() << " ";
			aux = aux->get_previous();
		}
	}
	else {
		std::cout << "\nvacia\n";
	}
}

template <typename T>
T* sacar_ultimo(NodoDoble<T>** head) {
	if (empty(head))
		return nullptr;
	NodoDoble<T>* aux = *head;
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
T* sacar(NodoDoble<T>** head, T& element) {
	if (empty(head))
		return nullptr;

	NodoDoble<T>* aux = *head;
	NodoDoble<T>* prev = *head;
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

#endif // !LISTADOBLE_H