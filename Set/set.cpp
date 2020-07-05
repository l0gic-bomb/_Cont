#include "set.h"
#include <iostream>

template<typename T>
inline Value<T>::Value(): value(0), prew(nullptr), next(nullptr), parent(nullptr)
{}

template<typename T>
inline Value<T>::Value(const T& val): value(val), prew(nullptr), next(nullptr), parent(nullptr)
{}

template<typename T>
Value<T>::Value(const Value<T>& _val): value(_val.value), prew(_val.prew), next(_val.next), parent(_val.parent)
{}

template<class T, class Alloc>
inline void Set<T, Alloc>::destroy(Value<T>* p)
{
    if (p != nullptr)
    {
        destroy(p->prew);
        destroy(p->next);
        traits::destroy(alloc, p);
        traits::deallocate(alloc, p, 1);
    }
}

template<class T, class Alloc>
void Set<T, Alloc>::kill_container(Value<T>* finder)
{
    Value<T>* ptr = finder->parent;

    if (ptr->next == finder)
        ptr->next = nullptr;
    else
        ptr->prew = nullptr;
}

template<class T, class Alloc>
Value<T>* Set<T, Alloc>::succ(Value<T>* ro)
{
    Value<T>* p = ro;

    if (root->value < p->value)
    {
        if (p->next != nullptr)
        {
            p = p->next;
            while (p->prew != nullptr)
                p = p->prew;
            return p;
        }
    }

    else if (root->value >= p->value)
    {
        if (p->prew != nullptr)
        {
            p = p->prew;
            while (p->next != nullptr)
                p = p->next;
            return p;
        }
    }
    return ro;
}

template<class T, class Alloc>
size_t Set<T, Alloc>::size() const
{
    return size;
}

template<class T, class Alloc>
Value<T>* Set<T, Alloc>::ret_root()
{
    return root;
}

template<class T, class Alloc>
Set<T, Alloc>::Set(): sz(0)
{}

template<class T, class Alloc>
Set<T, Alloc>::~Set() {
    destroy(root);
}

template<class T, class Alloc>
bool Set<T, Alloc>::empty() const
{
    if (ret_root() == nullptr)
        return 1;
    return 0;
}


template<class T, class Alloc>
const T& Set<T, Alloc>::min_elem() const
{
    if (this->empty())
        throw(std::exception());
    return begin().var->value;
}

template<class T, class Alloc>
const T& Set<T, Alloc>::max_elem() const
{
    if (this->empty())
        throw(std::exception());
    return end().var->value;
}

template<class T, class Alloc>
const T& Set<T, Alloc>::insert(const T& val)
{
    if (this->root == nullptr)
    {
        root = traits::allocate(alloc,1);
        traits::construct(alloc, root, val);
        ++this->size;
        return root->value;
    }

    Value<T>** var = &root;
    Value<T>** var_prew = &root;

    while ((*var) != nullptr && (*var)->value != val)
    {
        while ((*var) != nullptr && val > (*var)->value)
        {
            var_prew = var;
            var = &((*var)->next);
        }
        while ((*var) != nullptr && val < (*var)->value)
        {
            var_prew = var;
            var = &((*var)->prew);
        }
    }

    if ((*var) == nullptr)
    {
        (*var) = traits::allocate(alloc,1);
        traits::construct(alloc, *var, val);
    }

    ++this->size;
    (*var)->parent = *var_prew;
    return (*var)->value;
}

template<class T, class Alloc>
void Set<T, Alloc>::erase(const T val)
{
    if (this->empty())
        throw(std::exception());

    Value<T>* finder = this->find(val);

    if (finder->prew == nullptr && finder->next == nullptr)
    {
        kill_con(finder);
        traits::destroy(alloc, finder);
        traits::deallocate(alloc,finder,1);
        return;
    }
    else if (finder->prew != nullptr && finder->next != nullptr)
    {
        Value<T>* m = this->succ(finder);

        if (m->next == nullptr && m->prew == nullptr)
        {
            finder->value = m->value;
            kill_con(m);
            traits::destroy(alloc, m);
            traits::deallocate(alloc,m,1);
        }

        else if (m->next == nullptr && m->prew != nullptr)
        {
            Value<T> k = *m->prew;
            delete m->prew;
            m->prew = nullptr;
            finder->value = m->value;
            m->value = k.value;
            m->next = k.next;
            m->prew = k.prew;

        }

        else if (m->next != nullptr && m->prew == nullptr)
        {
            Value<T> k = *m->next;
            delete m->next;
            m->next = nullptr;
            finder->value = m->value;
            m->value = k.value;
            m->next = k.next;
            m->prew = k.prew;
        }

    }

    else
    {
        if (finder->next != nullptr)
        {
            Value<T> _val = *(finder->next);
            delete finder->next;
            finder->value = _val.value;
            finder->next = _val.next;
            finder->prew = _val.prew;
        }
        else if (finder->prew != nullptr)
        {
            Value<T> _val = *(finder->prew);
            delete finder->prew;
            finder->value = _val.value;
            finder->next = _val.next;
            finder->prew = _val.prew;
        }
    }
    --sz;
}

template<class T, class Alloc>
void Set<T, Alloc>::print_tree(Value<T>* p)
{
    if (root == nullptr)
        throw(std::exception());
    if (p != nullptr) {
        print_tree(p->prew);
        std::cout << p->value << " ";
        print_tree(p->next);
    }
}

template<class T, class Alloc>
Value<T>** Set<T, Alloc>::find_is_point(const T& val)
{
    if (this->empty()) throw(std::exception());
    Value<T>* var = root;
    while (var != nullptr && val != var->value) {
        while (var != nullptr && val > var->value) var = var->next;
        while (var != nullptr && val < var->value) var = var->prew;
    }
    if (var == nullptr) throw(std::exception());
    else return &var;
}

template<class T, class Alloc>
Value<T>* Set<T, Alloc>::find(const T& val)
{
    return *(find_is_point(val));
}
