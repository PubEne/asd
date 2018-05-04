#include <iostream>

namespace ASD
{
    template<typename T>
    struct node
    {
        explicit node(const T& key) : m_degree{0}, m_parent{nullptr}, m_child{nullptr}, m_sibling{nullptr}, m_key{key} {}  

        size_t m_degree;
        node*  m_parent;
        node*  m_child;
        node*  m_sibling;
        T      m_key;
    };
    constexpr size_t f(const size_t& n)
    {
        return n;
    }
}

int main()
{

}
