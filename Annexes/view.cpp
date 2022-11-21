#include"view.hpp"
#include<array>
#include<vector>
#include<iostream>
#include<type_traits>

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

    std::cout << std::boolalpha; 

    // Test create_view functions    

    auto v1 = create_view(ints);
    std::cout << "Does v1 has the expected type: " 
        << std::is_same_v<decltype(v1), view<std::vector<int>>> << std::endl;
    print_view(v1);
    
    auto v2 = create_view(ints, 3, 5);
    std::cout << "Does v2 has the expected type: " 
        << std::is_same_v<decltype(v2), view<std::vector<int>>> << std::endl;
    print_view(v2);
    
    auto v3 = create_view(ints, 3, 5);
    std::cout << "Does v3 has the expected type: " 
        << std::is_same_v<decltype(v3), view<std::array<std::string, 7>>> << std::endl;
    print_view(v3);

    // Test view of views

    auto large_set_of_towns = create_view(towns, 1, 5);
    auto small_set_of_towns = create_view(large_set_of_towns, 2, 4);
    std::cout << "Does large_set_of_towns and small_set_of_towns have the same type: " 
        << std::is_same_v<decltype(large_set_of_towns), decltype(small_set_of_towns)> << std::endl;
    print_view(large_set_of_towns);
    print_view(small_set_of_towns);

    // Test spaceship operator
    std::cout << "Is large_set_of_towns a strict superset of small_set_of_towns: " 
        << (large_set_of_towns > small_set_of_towns) << std::endl;
    std::cout << "Is large_set_of_towns a strict subset of small_set_of_towns: " 
        << (large_set_of_towns  < small_set_of_towns) << std::endl;

    auto another_set_of_towns = create_view(towns, 1, 3);
    std::cout << "Is another_set_of_towns a superset of small_set_of_towns: " 
        << (another_set_of_towns >= small_set_of_towns) << std::endl;
    std::cout << "Is another_set_of_towns a subset of small_set_of_towns: " 
        << (another_set_of_towns <= small_set_of_towns) << std::endl;
    std::cout << "Are another_set_of_towns and subset of small_set_of_towns non comparable: " 
        << ((another_set_of_towns <=> small_set_of_towns) == std::partial_ordering::unordered) << std::endl;
}
