#include "List.h"

template <typename data>
List<data>::List() : head(NULL), _size(0)
{
    List::free();
    std::cout << "list create..." << std::endl;
}
template <typename data>
int List<data>::add(const data &new_data)
{
    node *last = head;
    node *p = new node;
    p->value = new_data;
    p->key = _size;
    p->next = NULL;

    if (last)
    {
        while (last->next)
        {
            last = last->next;
        }
        last->next = p;
    }
    else
    {
        head = p;
    }
    ++_size;
    return this->_size;
}

template <typename data>
List<data> &List<data>::operator<<(const data &new_data)
{
    this->add(new_data);
    return *this;
}

template <typename data>
data &List<data>::operator[](int index)
{
    node *last = head;
    if (last)
    {
        while (last)
        {
            if (last->key == index)
            {
                return last->value;
            }
            last = last->next;
        }
    }
    exit(0);
}

template <typename data>
List<data>::~List()
{
    this->free();
    std::cout << "list del.." << std::endl;
}

template <typename data>
List<data>::node::~node()
{
    std::cout << key << "\'" << value << " node del.." << std::endl;
}

template <typename data>
List<data> &List<data>::free()
{
    node *last = head;
    node *temp = last;
    while (last)
    {
        temp = last->next;
        delete last;
        last = temp;
    }
    head = NULL;
    _size = 0;
    return *this;
}

template <typename data>
List<data> &List<data>::del(int index)
{
    node *last = head;
    int i;
    if (index == 0)
    {
        head = last->next;
        delete last;
        last = head;
        i = 0;
        while (last)
        {
            last->key--;
            last = last->next;
        }
        _size--;
        return *this;
    }
    else if (index > 0)
    {
        for (i = 0; i < index - 1; i++)
        {
            last = last->next;
        }
        node *temp = last->next;
        last->next = temp->next;
        delete temp;
        i = last->key;
        last = last->next;
        while (last)
        {
            last->key = ++i;
            last = last->next;
        }
        _size--;
    }
    else
    {
        return *this;
    }
    return *this;
}