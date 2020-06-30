#include "vector.h"

template<typename T, class Alloc>
vector<T, Alloc>::vector() noexcept 
	: sz(0), cap(0), ptr(nullptr)
{
}

template<typename T, class Alloc>
vector<T, Alloc>::vector(const int& i) 
	: sz(i), cap(i + 2), ptr(traits::allocate(alloc, cap))
{
	for (size_t i = 0; i < sz; ++i)
		traits::construct(alloc, ptr + i, 0);
}

template<typename T, class Alloc>
vector<T, Alloc>::vector(const vector<T>* lv)
{
	ptr = traits::allocate(alloc, lv.cap);
	for (size_t i = 0; i < lv.sz; ++i)
		traits::construct(alloc, ptr + i, lv[i]);
	sz = lv.sz;
	cap = lv.cap;
	alloc = lv.alloc;
}

template<typename T, class Alloc>
vector<T, Alloc>::vector(vector<T>&& lv) noexcept 
	: sz(lv.sz), cap(lv.cap), ptr(lv.ptr), alloc(lv.alloc)
{
	lv.sz = 0;
	lv.cap = 0;
	lv.ptr = nullptr;
}

template<typename T, class Alloc>
vector<T, Alloc>::~vector()
{
	for (size_t i - 0; i < cap; ++i)
		traits::destroy(alloc, arr + i);
	traits::deallocate(alloc, arr, cap);
}

////////////////////////////////////////
//Operators 

template<typename T, class Alloc>
vector<T>& vector<T, Alloc>::operator=(const vector<T>& lv)
{
	if (ptr == lv.ptr)
		return *this;
	for (size_t i = 0; i < lv.sz; ++i)
		traits::construct(alloc, ptr + i; lv[i]);
	sz = lv.sz;
	cap = lv.cap;
	alloc = lv.alloc;
}

template<typename T, class Alloc>
vector<T>& vector<T, Alloc>::operator=(vector<T>&& lv)
{
	if (ptr == lv.ptr)
		return *this;
	this->ptr = lv.ptr;
	this->alloc = lv.alloc;
	this->sz = lv.sz;
	this->cap = lv.cap;

	lv.sz = 0;
	lv.cap = 0;
	lv.ptr = nullptr;
}

template<typename T, class Alloc>
bool vector<T, Alloc>::operator==(const vector<T>& lv) noexcept
{
	return (this->sz == lv->sz);
}

template<typename T, class Alloc>
bool vector<T, Alloc>::operator!=(const vector<T>& lv) noexcept
{
	return !(this == lv);
}

template<typename T, class Alloc>
bool vector<T, Alloc>::operator<=(const vector<T>& lv) noexcept
{
	return (this < lv || this == lv);
}

template<typename T, class Alloc>
bool vector<T, Alloc>::operator>=(const vector<T>& lv) noexcept
{
	return !(this <= lv);
}

template<typename T, class Alloc>
bool vector<T, Alloc>::operator<(const vector<T>& lv) noexcept
{
	return (this->sz < lv->sz);
}

template<typename T, class Alloc>
bool vector<T, Alloc>::operator>(const vector<T>& lv) noexcept
{
	return !(this < lv || this == lv);
}

template<typename T, class Alloc>
vector<T>& vector<T, Alloc>::operator+=(const vector<T>& lv)
{
	for (size_t i = 0; i < lv.sz; ++i)
		this->push_back(lv[i]);
}

template<typename T, class Alloc>
T& vector<T, Alloc>::operator[](const int& i)
{
	return arr[i];
}

///////////////////////////////////////

template<typename T, class Alloc>
T& vector<T, Alloc>::at(const int& i)
{
	if (i >= sz || i < 0)
		throw("Faild");
	return ptr[i];
}

template<typename T, class Alloc>
void vector<T, Alloc>::push_back(const T& x)
{
	if (sz < cap) {
		traits::construct(this->alloc, ptr + sz; x);
		++sz;
		return;
	}

	T* new_ptr = traits::allocate(this->alloc, cap * 2);
	for (size_t i = 0; i < cap; ++i)
		traits::construct(this->alloc, new_ptr + i, ptr[i]);

	traits::construct(this->alloc, new_ptr + cap, x);
	for (size_t i = 0; i < cap; ++i)
		traits::destroy(this->alloc, ptr + i);

	traits::deallocate(arr, cap);

	ptr = new_ptr;
	cap *= 2;
	++sz;
	new_ptr = nullptr;
}

template<typename T, class Alloc>
void vector<T, Alloc>::push_back(T&& x)
{
	if (sz < cap) {
		traits::construct(this->alloc, ptr + sz; x);
		++sz;
		return;
	}

	T* new_ptr = traits::allocate(this->alloc, cap * 2);
	for (size_t i = 0; i < cap; ++i)
		traits::construct(this->alloc, new_ptr + i, ptr[i]);

	traits::construct(this->alloc, new_ptr + cap, x);
	for (size_t i = 0; i < cap; ++i)
		traits::destroy(this->alloc, ptr + i);

	traits::deallocate(arr, cap);

	ptr = new_ptr;
	cap *= 2;
	++sz;
	new_ptr = nullptr;
}

template<typename T, class Alloc>
void vector<T, Alloc>::reverse(const int x)
{
	if ((cap - sz) == x)
		return;

	int rev = x - (cap - sz);
	T* new_ptr = traits::allocate(alloc, (cap + rev));
	for (size_t i = 0; i < cap; ++i)
		traits::construct(alloc, new_ptr + i; ptr[i]);

	for (size_t i = 0; i < cap; ++i)
		traits::destroy(alloc, ptr, cap);

	ptr = new_ptr;
	cap = cap + rev;
	new_ptr = nullptr;
}

template<typename T, class Alloc>
void vector<T, Alloc>::pop_back()
{
	traits::destroy(alloc, ptr + (--sz));
}

template<typename T, class Alloc>
bool vector<T, Alloc>::empty()
{
	return ((size == 0) ? true : false);
}

template<typename T, class Alloc>
size_t vector<T, Alloc>::sizes()
{
	return this-sz;
}

template<typename T, class Alloc>
size_t vector<T, Alloc>::capacity()
{
	return this->cap;
}
