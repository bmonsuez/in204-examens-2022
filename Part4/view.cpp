#include"view.hpp"
#include<iostream>
// Overloaded operator to print the content of a view (as exposed in the annex)
template<typename charT>
std::basic_ostream<charT>& operator << (
    std::basic_ostream<charT>& output_stream, 
    const view& view)
{
    auto start = view.begin();
    auto end = view.end();
    output_stream << "[";
    while(start != end)
    {
        output_stream << *start;
        start ++;
        if(start == end)
            break;
        output_stream << ", ";
    }
    output_stream << "]";
    return output_stream;
}

void print_view(const view& v)
{
    std::cout << "number of elements in container: " << v.get_container().size() << std::endl;
    std::cout << "range: [" << v.get_first_index() << ", " << v.get_last_index() << "]" << std::endl;
    std::cout << "size: " << v.size() << std::endl;
    std::cout << "elements: " << v << std::endl;
}

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7 };
    view v1(vec);
    print_view(v1);
    view v2(vec, 3, 5);
    print_view(v2);
}