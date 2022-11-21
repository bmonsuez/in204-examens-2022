#pragma once
#include<vector>

class view
{
private:
    std::vector<int>& m_container;
    int m_first_index;
    int m_last_index;

public:
    explicit view(std::vector<int>& container):
        view(container, 0, (int)container.size()-1)
        {}
    view(std::vector<int>& container, 
        int first_index, int last_index):
        m_container(container),
        m_first_index(first_index),
        m_last_index(last_index)
    {}

    view(const view&) = default; 

    int get_first_index() const { return m_first_index; }
    int get_last_index() const { return m_last_index; }
    std::vector<int>& get_container() const { return m_container; }

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
};
