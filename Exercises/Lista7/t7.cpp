#include <iostream>

namespace ASD
{
    class UnionFind final
    {
        public:
            explicit UnionFind(const size_t& n) : m_parent{new size_t[n]},m_rank{new size_t[n]}
            {
                for(size_t i = 0; i < n; ++i)
                {
                    m_parent[i] = i;
                    m_rank[i]   = 0;
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
                delete[] m_parent;
                delete[] m_rank;
            }
        private:
            size_t* m_parent;
            size_t* m_rank;
    };
    size_t countIslands(const size_t& n, const bool a[][5])
    {
        UnionFind obj(n*n);
        for(size_t i = 0; i < n; ++i)
            for(size_t j = 0; j < n; ++j)
            {
                if(!a[i][j])
                    continue;
                if(i+1 < n && a[i+1][j])
                    obj.make_union(i*n+j,(i+1)*n+j);
                if(i-1 >= 0 && a[i-1][j])
                    obj.make_union(i*n+j,(i-1)*n+j);
                if(j-1 >= 0 && a[i][j-1])
                    obj.make_union(i*n+j,i*n+j-1);
                if(j+1 < n && a[i][j+1])
                    obj.make_union(i*n+j,i*n+j+1); 
            }
        bool temp[n] = {0};
        size_t numberOfIslands = 0;
        for(size_t i = 0; i < n; ++i)
            for(size_t j = 0; j < n; ++j)
                if(a[i][j])
                {
                    size_t x = obj.find(i*n+j);
                    if(!temp[x]++)
                        ++numberOfIslands;
                }  
        return numberOfIslands;
    }
}
int main()
{
    /* 0 - sea, 1 - island */
    constexpr size_t n = 5;
    bool t[n][n] = {{1,1,0,0,0},
                    {0,1,0,0,1},
                    {0,0,1,0,0},
                    {0,0,0,0,0},
                    {1,0,1,0,1}};
    std::cout << ASD::countIslands(n,t) << std::endl;
}
