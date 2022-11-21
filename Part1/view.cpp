#include"view.hpp"
#include<iostream>

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7 };
    view v1(vec);
    view v2(vec, 3, 5);
}