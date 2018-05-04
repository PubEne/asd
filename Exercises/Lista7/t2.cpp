#include <iostream>
#include <list>
#include <vector>

namespace ASD
{
    template<typename T = int,size_t size=100>
    class BinomialTree final
    {
        public:
            constexpr BinomialTree(){}
            ~BinomialTree(){}
        private:
            struct node
            {
                constexpr explicit node(const T& key) : m_parent{nullptr}, m_child{nullptr}, m_sibling{nullptr}, m_key{key}, m_degree{0}  {}  

                node*  m_parent;
                node*  m_child;
                node*  m_sibling;
                T      m_key;
                size_t m_degree;
            };
            std::vector<node*> m_v;
    };

    constexpr size_t f(const size_t& n)
    {
    }
}

int main()
{
    std::list<ASD::BinomialTree<>> binomial_heap;
    std::cout << sizeof(ASD::BinomialTree<>) << std::endl;
}

