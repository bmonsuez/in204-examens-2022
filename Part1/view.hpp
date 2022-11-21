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
};
