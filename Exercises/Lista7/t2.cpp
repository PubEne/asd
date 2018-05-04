#include <iostream>
#include <list>
#include <vector>

namespace ASD
{
    template<typename T = int,size_t size=100>
    class BinomialHeap final
    {
        public:
            constexpr BinomialHeap() {}
            void insert();
            void print();
            void find();
            T get_max();
            void make_union();
            void merge();
            ~BinomialHeap()
            {
                for(auto& m_tree : m_trees)
                    if(m_tree)
                        delete m_tree;
            }
        private:
            class BinomialTree final
            {
                private:
                    struct node; // for further purposes
                public:
                    constexpr BinomialTree() : m_nodes(10) {}
                    node* createNode(const T& key)
                    {
                        m_nodes.emplace_back(new node(key));
                    }
                    ~BinomialTree()
                    {
                        for(auto& m_node : m_nodes)
                            if(m_node)
                                delete m_node;
                    }
                private:
                    struct node
                    {
                        constexpr explicit node(const T& key) : m_parent{nullptr}, m_child{nullptr}, m_sibling{nullptr}, m_key{key}, m_degree{0} {}  
                        node*  m_parent;
                        node*  m_child;
                        node*  m_sibling;
                        T      m_key;
                        size_t m_degree;
                    };
                    std::vector<node*> m_nodes;
            };
            std::list<BinomialTree*> m_trees;
    };
    //number of nodes n in binomial tree  - 2^n
    constexpr size_t f(const size_t& n)
    {
    }
}

int main()
{
    ASD::BinomialHeap<> heap;
}

