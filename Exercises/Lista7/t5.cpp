#include <iostream>

namespace ASD
{
    class UnionFind final
    {
        public:
            UnionFind(const size_t& n) : m_parent{new size_t[n]}, m_rank{new size_t[n]}
            {
                for(size_t i = 0; i < n; ++i)
                {
                    m_parent[i] = i;
                    m_rank[i] = 0;
                }
            }
            size_t find(const size_t& i)
            {
                if(m_parent[i] == i)
                    return i;
                return m_parent[i] = find(m_parent[i]);
            }
            void make_union(const size_t& i,const size_t& j)
            {
                size_t a = find(i);
                size_t b = find(j); 
                if(a!=b)
                    if(m_rank[a] < m_rank[b])
                        m_parent[a] = b;
                    else if(m_rank[b] < m_rank[a])
                        m_parent[b] = a;
                    else
                    {
                        m_parent[a] = b;
                        ++m_rank[b];
                    }
            }
            ~UnionFind()
            {
                delete[] m_rank;
                delete[] m_parent;
            }
        private:
            size_t* m_parent;
            size_t* m_rank;
    };
}
int main()
{
    ASD::UnionFind obj(25);
}
