#pragma once
#include <iostream>

// Элемент списка
template<typename T>
struct Node {
	Node<T>* _prev;
	Node<T>* _next;
	T _data;

	Node();
	// Конструктор с параметрами
	Node(Node<T>* next, Node<T>* prev, const T& data);
	// Деструктор
	~Node();
};

template<typename T>
class List
{
public:
	class Iterator;

	std::size_t size() const;

	virtual ~List() {};





private:
	Node<T>* current;
	std::size_t _size;

};


template<typename T>
class List<T>::Iterator {
public:
	Iterator() : _node(nullptr) {};
	Iterator(const Node<T> t) : _node(&T) {}

	Iterator& operator++() {
		_node = _node->_next;
		return *this;
	}

	Iterator& operator++(int) {
		Iterator iterator(_node);
		_node = _node->_next;
		return *this;
	}

	Iterator& operator--() {
		_node = _node->_prev;
		return *this;
	}

	Iterator& operator--(int) {
		Iterator iterator(_node);
		_node = _node->_prev;
		return *this;
	}

	bool operator==(const Iterator& iter) const {
		return (_node == iter._node);
	}

	bool operator!=(const Iterator& iter) const {
		return (_node != iter._node);
	}

	Iterator operator- (int& count) {
		Iterator iter(_node);
		while (--count)
			++iter;
		return iter;
	}

	Iterator operator+ (int& count) {
		Iterator iter(_node);
		while (--count)
			--iter;
		return iter;
	}

	T& operator*() {
		return ((Node<T>*)_node)->_data;
	}

	T& operator->() {
		return &((Node<T>*)_node)->_data;
	}


private:
	Node<T>* _node;
};
