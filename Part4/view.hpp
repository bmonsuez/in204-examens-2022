#pragma once

#include<vector>

class view
{
public:
    using container=std::vector<int>;
    
    using value_type = typename container::value_type;
    using reference = typename container::reference;
    using const_reference = typename container::const_reference;

    using iterator = typename container::iterator;
    using const_iterator = typename container::const_iterator;
    using size_type = typename container::size_type;

    // Additional type (as exposed in the complementary section of part 4)
    using difference_type = container::difference_type;

private:
    container& m_container;
    int m_first_index;
    int m_last_index;

public:

    explicit view(container& container):
        view(container, 0, (int)container.size()-1)
        {}
    view(container& container, 
        int first_index, int last_index):
        m_container(container),
        m_first_index(first_index),
        m_last_index(last_index)
    {}

    view(const view&) = default; 

    // Access methods
    int get_first_index() const { return m_first_index; }
    int get_last_index() const { return m_last_index; }
    container& get_container() const { return m_container; }

    // State
    bool empty() const { return m_last_index < m_first_index; }
    size_type size()  const { return (size_type)(m_last_index + 1 - m_first_index); }

    // Iterators
    iterator begin() { return m_container.begin() + m_first_index; }
    const_iterator begin() const { return m_container.begin() + m_first_index; }
    iterator end() { return m_container.begin() + m_last_index + 1; }
    const_iterator end() const { return m_container.begin() + m_last_index + 1; }

    // Comparison operators
    bool operator == (const view& another_view) const
    {
        return &m_container == &another_view.m_container 
            && m_first_index == another_view.m_first_index
            && m_last_index == another_view.m_last_index;
    }
#if __cplusplus < 202002L
    bool operator != (const view& another_view) const
    {
        return &m_container != &another_view.m_container 
            || m_first_index != another_view.m_first_index
            || m_last_index != another_view.m_last_index;
    }
#endif

    // Additional methods (as exposed in the complementary section of part 4)
    const_iterator cbegin() const { return m_container.begin() + m_first_index; }
    const_iterator cend() const { return m_container.begin() + m_last_index + 1; }
    size_type max_size() const { return size(); }    
    void swap(view& another_view)
    {
        std::swap(m_container, another_view.m_container);
        std::swap(m_first_index, another_view.m_first_index);
        std::swap(m_last_index, another_view.m_last_index);
    }
};


// Additional functions (as exposed in the complementary section of part 4)
namespace std
{
    void swap(view& first_view, view& second_view)
    {
        first_view.swap(second_view);
    }
}
