#pragma once
#include<string>
#include<sstream>

namespace std

{

template<typename charT, typename char_traits> 
std::basic_string<charT, char_traits> place_holder = 
    std::basic_string<charT, char_traits>({(charT)'{', (charT)'}' });

template<typename charT>
std::basic_string<charT> format(
    const charT* format_string)
{
    return std::basic_string<charT>(format_string); 
}

template<typename charT, typename char_traits>
std::basic_string<charT, char_traits> format(
    std::basic_string<charT, char_traits> format_string)
{
    return format_string;
}

template<
    typename charT,
    typename Arg, typename... Args>
std::basic_string<charT> format(
    const charT* format_string,
    Arg argument, Args... next_arguments)
{
    return format(std::basic_string<charT>(format_string), 
        argument, next_arguments...);
}

template<
    typename charT, typename char_traits,
    typename Arg, typename... Args>
std::basic_string<charT, char_traits> format(
    std::basic_string<charT, char_traits> format_string,
    Arg argument, Args... next_arguments)
{
    using string_type = std::basic_string<charT, char_traits>;
    std::basic_stringstream<charT, char_traits> buffer;
    auto place_holder_pos = format_string.find(place_holder<charT, char_traits>);
    if(place_holder_pos == string_type::npos)
        return format_string;
    if(place_holder_pos > 0)
        buffer << format_string.substr(0, place_holder_pos);
    buffer << argument;
    buffer << format(
        format_string.substr(place_holder_pos + 2), next_arguments...);
    return buffer.str();
}

}
