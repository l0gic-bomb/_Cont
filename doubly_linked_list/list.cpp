#include "list.h"

/*_____________________NODE_______________________*/

// Конструктор по умолчанию
// (при создании ссылаемся на себя же)
template<typename T>
inline Node<T>::Node() : _next(this), _prev(this)
{
}

template<typename T>
Node<T>::Node(Node<T>* next, Node<T>* prev, const T& data) 
	: _next(next), _prev(prev), _data(data)
{
	// Сбиваем указатели на следующий элемент и предыдущий
	prev->next = this;
	next->prev = this;	
}

template<typename T>
Node<T>::~Node()
{
	_prev->next = _next;
	_next->prev = _prev;
}


template<typename T>
std::size_t List<T>::size() const
{
	std::size_t size;
	return size;
}

