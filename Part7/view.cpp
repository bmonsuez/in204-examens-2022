#include"view.hpp"
#include<array>
#include<vector>
#include<iostream>

// Overloaded operator to print the content of a view (as exposed in the annex)
template<typename charT, typename containerT>
std::basic_ostream<charT>& operator << (
    std::basic_ostream<charT>& output_stream, 
    const view<containerT>& view)
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

template<typename containerT>
void print_view(const view<containerT>& v)
{
    std::cout << "number of elements in container: " << v.get_container().size() << std::endl;
    std::cout << "range: [" << v.get_first_index() << ", " << v.get_last_index() << "]" << std::endl;
    std::cout << "size: " << v.size() << std::endl;
    std::cout << "elements: " << v << std::endl;
}

int main()
{
    std::vector<int> ints = {1, 2, 3, 4, 5, 6, 7 };
    std::array<std::string, 7> towns = {
         "Paris", "Londres", "Bruxelles", 
         "Lisbonne", "Madrid", "Berlin", "Rome"};
    
    view<std::vector<int>> v1(ints);
    print_view(v1);
    view<std::vector<int>> v2(ints, 3, 5);
    print_view(v2);
    view<std::array<std::string, 7>> v3(towns , 3, 5);
    print_view(v3);

    // Test validation of boundaries
    try
    {
        view<std::array<std::string, 7>> v4(towns, 3, 8);
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }    

    // Test index access to the view content.

    std::cout << "Enumerating v3:\n";
    for(int i = 0; i < v3.size(); i++)
        std::cout << "   " << v3[i] << std::endl;
}