#include"view.hpp"
#include<iostream>

void print_view(const view& v)
{
    std::cout << v.get_container().size() << "[" << v.get_first_index() << ", " << v.get_last_index() << "]" << std::endl;
}

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7 };
    view v1(vec);
    print_view(v1);
    view v2(vec, 3, 5);
    print_view(v2);
}