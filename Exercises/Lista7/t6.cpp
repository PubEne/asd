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
    bool DoesPathExistA(const size_t& n,const bool t[][5])
    {
        if(!t[0][0])
            return 0;
        UnionFind obj(n*n); 
        for(size_t i = 0; i < n; ++i)
            for(size_t j = 0; j < n; ++j)
            {
                if(t[i][j])
                {
                    if(i+1 < n && t[i+1][j]) //right
                        obj.make_union(i*n+j,(i+1)*n+j);
                    if(j+1 < n && t[i][j+1]) //down
                        obj.make_union(i*n+j,i*n+j+1);
                 }
            }
        return obj.find(0) == obj.find(n*n-1) ? 1 : 0;
    }
    bool DoesPathExistB(const size_t& n,const bool t[][5])
    {
        UnionFind obj(n*n); 
        for(size_t i = 0; i < n; ++i)
            for(size_t j = 0; j < n; ++j)
            {
                if(t[i][j])
                {
                    if(i+1 < n && t[i+1][j]) //right
                        obj.make_union(i*n+j,(i+1)*n+j);
                    if(i-1 >= 0 && t[i-1][j]) //left
                        obj.make_union(i*n+j,(i-1)*n+j);
                    if(j+1 < n && t[i][j+1]) //down
                        obj.make_union(i*n+j,i*n+j+1);
                 }
            }

        for(size_t i = 0; i < n; ++i)
            if(t[0][i])
            {
                for(size_t j = 0; j < n; ++j)
                    if(t[n-1][j])
                    {
                        //std::cout << obj.find(i*n+j) << "," << obj.find(i*n+j) << std::endl;
                        if(obj.find(i) == obj.find(i*n+n-1))
                            return 1;
                    }
            }
        return 0;
    }
}
int main()
{
    constexpr size_t n = 5;
    constexpr bool t[n][n] = {{1,1,0,0,0},
                              {0,1,0,0,1},
                              {0,0,1,0,0},
                              {0,0,0,0,0},
                              {1,0,1,0,1}};

    constexpr bool t2[n][n] = {{1,1,0,0,0},
                               {1,0,0,0,1},
                               {1,1,0,0,0},
                               {0,1,0,1,0},
                               {1,1,1,1,1}};

    constexpr bool t3[n][n] = {{1,0,0,0,0},
                               {1,1,0,0,1},
                               {0,1,0,0,0},
                               {0,1,0,1,0},
                               {1,1,1,0,1}};
    std::cout << ASD::DoesPathExistB(n,t3) << std::endl;
}
