#include <iostream>
#include <limits>
#include <algorithm>
#include <sstream>
#include <queue>
#include <fstream>
#include <vector>
#include <list>
#include <forward_list>
#include <string>

namespace ASD
{
    class UnionFind final
    {
        public:
            UnionFind(const size_t& n) : parent(n), rank(n,0)
            {
                for(size_t i = 0; i < n; ++i)
                    parent[i] = i;
            }
            size_t find(const size_t& i)
            {
                if(parent[i] != i)
                    parent[i] = find(parent[i]);
                return parent[i];
            }
            bool make_union(const size_t& i,const size_t& j)
            {
                size_t a = find(i);
                size_t b = find(j);
                if(a == b)
                    return 0;
                if(rank[a] > rank[b])
                    parent[b] = a;
                else
                {
                    parent[a] = b;
                    if(rank[a] == rank[b])
                        ++rank[b];
                } 
                return 1;
            }
        private:
            std::vector<int> parent;
            std::vector<int> rank;
    };
    class Graph final
    {
        private:
            struct Edge;
        public:
            explicit Graph(const size_t& num) : m_vertices(num), m_adj(num) {}
            explicit Graph(const std::string& filename) : m_vertices(0),m_adj(0)
            {
                std::ifstream inFile;
                inFile.open(filename);
                inFile >> m_vertices >> m_edges;

                m_adj.resize(m_vertices);
                for(auto& v : m_adj)
                {
                    v.resize(m_vertices);
                    for(auto& el : v)
                        el = {0,0};
                }
                if(inFile.is_open())
                {
                    Edge edge;
                    while(!inFile.eof() && inFile >> edge.m_src && inFile >> edge.m_dest && inFile >> edge.m_distance)
                        addEdge(edge);
                }
                inFile.close();
            }
            void printAdjacencyMatrix() const
            {
                std::cout << "\t     [AdjacencyMatrix]" << std::endl;
                std::cout << "\t";
                for(size_t i = 0; i < m_adj.size(); ++i)
                    std::cout << i << "   ";
                std::cout << std::endl;
                
                for(size_t i = 0; i < m_adj.size(); ++i)
                {
                    std::cout << i << " | [ ";
                    for(size_t j = 0; j < m_adj.size(); ++j)
                    {
                        if(i == j)
                            std::cout << "  =,";
                        else if(!m_adj[i][j].second)
                            std::cout << "  0,";
                        else
                            std::cout << "  " << m_adj[i][j].second << ",";    
                    }
                    std::cout << " ]\r\n";
                }
                std::cout << "\r\n"; 
            }
            void printMST()
            {
                std::vector<bool> mst(m_vertices,0);
                std::vector<std::pair<int,int>> resultSet(m_vertices);
                std::vector<int> key(m_vertices,std::numeric_limits<int>::max());
                key[0] = 0;
                resultSet[0].first = -1; 
                for(size_t i = 0; i < m_vertices; ++i)
                {
                    int vertex = getMinimumVertex(mst,key);
                    mst[vertex] = 1;
                    for(size_t j = 0; j < m_vertices; ++j)
                        if(m_adj[vertex][j].second > 0)
                            if(!mst[j] && m_adj[vertex][j].second < key[j])
                            {
                                key[j] = m_adj[vertex][j].second;
                                resultSet[j] = {vertex,key[j]};
                            }
                }

                std::cout << "\t     [MST]" << std::endl;
                size_t total_min_weight = 0;
                for(size_t i = 1; i < m_vertices; ++i)
                {
                    std::cout << "Edge: " << i << " - " << resultSet[i].first << " distance: " << resultSet[i].second << std::endl;
                    total_min_weight += resultSet[i].second;
                }
                std::cout << total_min_weight << std::endl;
                
            }
            void printShortestPath(const int& start = 0) const
            {
                std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> pq;     
                std::vector<int> distances(m_vertices,std::numeric_limits<int>::max());
                pq.push({0,start});
                
                distances[start] = 0;
                while(!pq.empty())
                {
                    int u = pq.top().second;
                    pq.pop();
                    for(const auto& v : m_adj[u])
                    {
                        int distance = v.second;
                        int vertex = v.first;
                        if(distances[vertex] > distances[u] + distance)
                        {
                            distances[vertex] = distances[u] + distance;
                            pq.push({distances[vertex],vertex});
                        } 
                    } 
                     
                }
                std::cout << "\t     [Dijkstra algorithm]" << std::endl;
                for(size_t i = 0; i < m_vertices; ++i)
                    std::cout << i << "\t" << distances[i] << std::endl;
            }
            void printShortestPath2()
            {
                std::vector<bool> mst(m_vertices,0);
                std::vector<int> distances(m_vertices,std::numeric_limits<int>::max());
                distances[0] = 0;
                for(size_t i = 0; i < m_vertices; ++i)
                {
                    int vertex = getMinimumVertex(mst,distances);
                    mst[vertex] = 1;

                    for(size_t j = 0; j < m_vertices; ++j)
                            if(!mst[j] && m_adj[vertex][j].second && distances[vertex] != std::numeric_limits<int>::max() && distances[vertex]+m_adj[vertex][j].second < distances[j])
                                distances[j] = distances[vertex] + m_adj[vertex][j].second;
                }
                std::cout << "\t     [Dijkstra algorithm]" << std::endl;
                for(size_t i = 0; i < m_vertices; ++i)
                    std::cout << i << "\t" << distances[i] << std::endl;
            }
            void addEdge(const size_t& src,const size_t& dest,const double& distance = 1)
            {
                m_adj[src].push_back({dest,distance});
                m_adj[dest].push_back({src,distance});
            }
            void addEdge(const Edge& edge)
            {
                m_adj[edge.m_src][edge.m_dest] = {edge.m_dest,edge.m_distance};
                m_adj[edge.m_dest][edge.m_src] = {edge.m_src,edge.m_distance};
            }
            size_t getNumberOfEdges() const
            {
                return m_edges;
            }
            size_t getNumberOfVertices() const
            {
                return m_vertices;
            }
            void printAdjacencyList() const
            {
                std::cout << "\t     [AdjacencyList]" << std::endl;
                size_t i = 0;
                for(const auto& v : m_adj)
                {
                    std::cout << i++ << "|--";
                    for(const auto& el : v)
                        if(el.second)
                            std::cout << el.second << "-->" << el.first << "|--";
                    std::cout << std::endl;
                }
            }
        private:
            struct Edge final
            {
                Edge(){}
                Edge(const size_t& src,const size_t& dest,const double& distance) : m_src(src), m_dest(dest), m_distance(distance) {}
                size_t m_src = 0;
                size_t m_dest = 0;
                double m_distance = 0;
            };
            int getMinimumVertex(const std::vector<bool>& mst,const std::vector<int>& key)
            {
                int min_key = std::numeric_limits<int>::max();
                int vertex = -1;
                for(size_t i = 0; i < m_vertices; ++i)
                    if(!mst[i] && min_key > key[i])
                    {
                        min_key = key[i];
                        vertex = i;
                    }
                return vertex;
            }
            std::vector<std::vector<std::pair<size_t,double>>> m_adj;
            size_t m_vertices;
            size_t m_edges;
    };
}

int main()
{
    ASD::Graph graph("t3txt.txt");;
    graph.printAdjacencyList();
    graph.printAdjacencyMatrix();
    graph.printMST();
    graph.printShortestPath();
    graph.printShortestPath2();
}
