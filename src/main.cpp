#include <iostream>

#include "library/containers/linkedlist.h"

using namespace rdi;

int main()
{
    ForwardList<int> lst;
    lst.push_front(1);
    lst.push_front(2);
    lst.push_front(3);
    lst.pop_front();

    for (int i : lst) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}
