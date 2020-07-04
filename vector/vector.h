#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <memory>

template<typename T, class Alloc = std::allocator<T>>
class vector
{
	T* ptr;
	size_t sz;
	size_t cap;
	Alloc alloc;

	/*
	using vec_type T;
	using ptr_vec_type = T*;
	using A = Alloc;
	*/

	using traits = std::allocator_traits<Alloc>;
	
public:
	vector() noexcept;
	vector(const int& i);
	vector(const vector<T>* lv);
	vector(vector<T>&& lv) noexcept;
	~vector();

	vector<T>& operator =(const vector<T>& lv);
	vector<T>& operator =(vector<T>&& lv);

	bool operator ==(const vector<T>& lv) noexcept;
	bool operator !=(const vector<T>& lv) noexcept;
	bool operator <=(const vector<T>& lv) noexcept;
	bool operator >=(const vector<T>& lv) noexcept;

	bool operator <(const vector<T>& lv) noexcept;
	bool operator >(const vector<T>& lv) noexcept;

	vector<T>& operator +=(const vector<T>& lv);
	//vector<T>  operator  +(const vector<T>& lv);

	T& operator [](const int& i);
	T& at(const int& i);

	void push_back(const T& x);
	void push_back(T&& x);

	void reverse(const int x);
	void pop_back();

	bool empty();

	size_t sizes();
	size_t capacity();

	struct iterator
	{
		T* ptr;

		iterator() {
			ptr = nullptr;
		}

		iterator(T* lv) {
			ptr = lv;
		}

		iterator(const iterator& a) {
			ptr = a.ptr;
		}

		iterator operator =(const iterator& rv)
		{
			this->ptr = rv.ptr;
		}

		iterator& operator ++() {
			++ptr;
			return *this;
		}

		iterator operator ++(int) {
			iterator np = *this;
			++ptr;
			return np;
		}

		T* operator [](const int& i) {
			return ptr[i];
		}

		T& operator *() {
			return *(this->ptr);
		}

		bool operator ==(const iterator& rv) {
			return(ptr == rv.ptr);
		}

		bool operator !=(const iterator& rv) {
			return !(*this == rv);
		}
	};

	iterator begin() {
		return iterator(ptr);
	}

	iterator end() {
		return iterator(&ptr[sz] + 1);
	}
};

#endif // VECTOR_H
