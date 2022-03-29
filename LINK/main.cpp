#include "link.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    List<int> list;
    list << 123 << 123 << 234;
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << list[i] << std::endl;
    }
    return 0;
}