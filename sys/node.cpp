#include <iostream>
struct data
{
    std::string name;
};


class array
{
private:
    data *node;
    int size;
public:
    array():node(NULL),size(0)
    {

    }
};