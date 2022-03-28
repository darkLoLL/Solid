#include <iostream>

template <typename data>
class List
{
private:
    struct node
    {
        int key;
        data value;
        node *next;
        node()
        {
            std::cout << "node create.." << std::endl;
        }
        ~node();
    };
    node *head;
    int _size;

public:
    List();
    int size()
    {
        return _size;
    }
    int add(const data &new_data);
    List &del(int index);
    List &free();
    List &operator<<(const data &new_data);
    data &operator[](int index);
    ~List();
};