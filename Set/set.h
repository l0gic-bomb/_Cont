#ifndef SET_H
#define SET_H

#include<memory>

template <typename T>
struct Value {
    T value;
    Value* prew;
    Value* next;
    Value* parent;

    Value();
    Value(const T& val);
    Value(const Value<T>& _val);
};

template <typename T, class Alloc = std::allocator<Value<T>>>
class Set {

public:
    Set();
    Set(const Set& rvl) = delete;
    Set operator =(const Set& rvl) = delete;
    ~Set();

    size_t size() const;
    Value<T>* ret_root();

    class iterator_tree;

    bool empty() const;

    const iterator_tree begin()
    {
        if (this->empty())
            throw(std::exception());
        Value<T>* var = root;
        while (var->prew != nullptr)
            var = var->prew;
        auto it = iterator_tree(var);
        return it;
    }

    const iterator_tree end()
    {
        if (this->empty())
            throw(std::exception());
        Value<T>* var = root;
        while (var->next != nullptr)
            var = var->next;
        return iterator_tree (var);
    }

    const T& min_elem() const;
    const T& max_elem() const;

    const T& insert(const T& val);

    void erase(const T val);

    void print_tree(Value<T>* p);

    Value<T>** find_is_point(const T& val);

    Value<T>* find(const T& val);

private:

    using traits = std::allocator_traits<std::allocator<Value<T>>>;
    static Value<T>* root;
    size_t sz;
    Alloc alloc;

    void destroy(Value<T>* ptr);
    void kill_container(Value<T>* finder);

    Value<T>* succ(Value<T>* ro);

};

template<typename T, class Alloc>
class Set<T, Alloc>:: iterator_tree
{
    Value<T>* var;
public:
    size_t size_of_set() {
        return 10;
    }

    iterator_tree() :var(nullptr)
    {}
    iterator_tree(Value<T>* _val) :var(_val)
    {}
    iterator_tree(const iterator_tree& rvl) :var(rvl.var)
    {}

    T& operator *() const {
        return var->value;
    }

    T* operator ->() const {
        return &var->value;
    }

    iterator_tree& begin_it() const {
        Value<T>* var = root;
        while (var->prew != nullptr) var = var->prew;
        return *this;
    }

    iterator_tree& end_it() {
        Value<T>* var = root;
        while (var->next != nullptr) var = var->next;
        return *this;
    }

    iterator_tree& operator ++() {
        if (var != nullptr) {
            if (var->next != nullptr) {
                var = var->next;
                while (var->prew != nullptr)
                    var = var->prew;
            }
            else if (var->next == nullptr && var->value < var->parent->value)
                var = var->parent;
            else if (var->next == nullptr && var->value > var->parent->value)
                var = var->parent->parent;
        }
        return *this;
    }

    bool operator !=(const iterator_tree& rvl) {
        return (this->var->value != *rvl);
    }
};


#endif // SET_H
