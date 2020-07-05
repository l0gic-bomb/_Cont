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

    const T& operator [](const int& i) const;
    T& at(const int& i);

    void push_back(const T& x);
    void push_back(T&& x);

    void reverse(const int x);
    void pop_back();

    bool empty() const;

    size_t sizes() const;
    size_t capacity() const;

    class iterator;

    iterator begin()
    {
        return iterator(ptr);
    }

    iterator end()
    {
        return iterator(&ptr[sz] + 1);
    }
};

template<typename T, class Alloc>
class vector<T, Alloc>::iterator
{
public:
    iterator() : current(nullptr)
    {}

    iterator(T* lv): current(lv)
    {}

    iterator(const iterator& a): current(a.current)
    {}

    iterator operator =(const iterator& rv)
    {
        this->current = rv.current;
    }

    iterator& operator ++()
    {
        ++current;
        return *this;
    }

    iterator operator ++(int)
    {
        iterator np = *this;
        ++current;
        return np;
    }

    T* operator [](const int& i)
    {
        return current[i];
    }

    T& operator* ()
    {
        return *(this->current);
    }

    bool operator ==(const iterator& rv) const
    {
        return (current == rv.current);
    }

    bool operator !=(const iterator& rv) const
    {
        return (*current != rv.current);
    }

private:
    T* current;
};


#endif // VECTOR_H
