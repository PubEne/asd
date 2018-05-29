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
            class min_priority_queue;
        public:
            explicit Graph(const size_t& num) : m_vertices(num), m_adj(num,std::vector<std::pair<size_t,double>>(num,{0,0})) {}
            explicit Graph(const std::string& filename) : m_vertices(0),m_adj(0)
            {
                std::ifstream inFile;
                inFile.open(filename);
                inFile >> m_vertices >> m_edges;

                m_adj.resize(m_vertices+1);
                for(auto& v : m_adj)
                {
                    v.resize(m_vertices+1);
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
                for(size_t i = 1; i < m_adj.size(); ++i)
                    std::cout << i << "   ";
                std::cout << std::endl;
                
                for(size_t i = 1; i < m_adj.size(); ++i)
                {
                    std::cout << i << " | [ ";
                    for(size_t j = 1; j < m_adj.size(); ++j)
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
            void printMST(const int& i)
            {
                if(i > m_adj.size()-1)
                    return;
                std::vector<int> prev(m_adj.size(),0);
                std::vector<double> distance(m_adj.size(),std::numeric_limits<double>::max());
                
                prev[i] = i;
                min_priority_queue pq(distance);

                pq.decrease_key(i,0);
                while(!pq.empty())
                {
                    unsigned j = pq.get_min();
                    for(const auto& node : m_adj[j])
                        if(distance[node.first] > node.second)
                        {
                            prev[node.first] = j;
                            distance[node.first] = node.second;
                            pq.decrease_key(node.first,node.second);
                        }
                }
                std::cout << "\t     [MST Tree2]" << std::endl;
                std::cout << "Edge\t Weight" << std::endl;
                for(size_t i = 2; i < prev.size(); ++i)
                    std::cout << prev[i] << "-" << i << "\t" << distance[i] << std::endl;
            }
      /*      void printMST()
            {
                std::vector<bool> mst(m_vertices+1,0);
                std::vector<std::pair<int,int>> resultSet(m_vertices+1);
                std::vector<int> key(m_vertices+1,std::numeric_limits<int>::max());
                key[0] = 0;
                resultSet[0].first = -1; 
                for(size_t i = 0; i < m_vertices+1; ++i)
                {
                    int vertex = getMinimumVertex(mst,key);
                    mst[vertex] = 1;
            
                    for(size_t j = 0; j < m_vertices+1; ++j)
                        if(m_adj[vertex][j].second > 0)
                            if(!mst[j] && m_adj[vertex][j].second < key[j])
                            {
                                key[j] = m_adj[vertex][j].second;
                                resultSet[j] = {vertex,key[j]};
                            }
                }

                std::cout << "\t     [MST]" << std::endl;
                for(size_t i = 1; i < m_vertices+1; ++i)
                    std::cout << "Edge: " << i << " - " << resultSet[i].first << " distance: " << resultSet[i].second << std::endl;
                
            }*/
            void printMSTKruskal()
            {
                Graph tree(m_adj.size()); 
                UnionFind uf(m_adj.size()); 
                std::vector<Edge> edges; 

                for(size_t i = 0; i < m_adj.size(); ++i)
                    for(const auto& el : m_adj[i])
                        if(el.first)
                            edges.emplace_back(Edge(i,el.first,el.second));
                std::sort(edges.begin(),edges.end(),[](const Edge& e1,const Edge& e2) { return e1.m_distance < e2.m_distance; });
                for(const auto& edge : edges)
                    if(uf.make_union(edge.m_src,edge.m_dest))
                        tree.addEdge(edge.m_src,edge.m_dest,edge.m_distance);
                tree.printAdjacencyList(0);
            }
            void printMSTPrim(const int& start = 1) const
            {
                std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> pq;     
                std::vector<double> distances(m_vertices+1,std::numeric_limits<double>::max());
                std::vector<int> parent(m_vertices+1,-1);
                std::vector<bool> inMST(m_vertices+1,false);
                pq.push({0,start});
                
                distances[start] = 0;
                while(!pq.empty())
                {
                    int u = pq.top().second;
                    std::cout << pq.top().first << std::endl;
                    pq.pop();
                    inMST[u] = 1;
                    for(const auto& v : m_adj[u])
                    {
                        double distance = v.second;
                        int vertex = v.first;
                        if(!inMST[vertex] && distances[vertex] > distance)
                        {
                            distances[vertex] = distance;
                            pq.push({distances[vertex],vertex});
                            parent[vertex] = u;
                        } 
                    } 
                     
                }
                std::cout << "\t     [MST Prim v.2]" << std::endl;
                for(size_t i = 2; i < m_vertices+1; ++i)
                    std::cout << parent[i] << "-"  << i << "\t" << distances[i] << std::endl;
            }
            void printShortestPath(const int& start = 1) const
            {
                std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> pq;     
                std::vector<double> distances(m_vertices+1,std::numeric_limits<double>::max());
                std::vector<double> weight;
                pq.push({0,start});
                
                distances[start] = 0;
                while(!pq.empty())
                {
                    int u = pq.top().second;
                    pq.pop();
                    for(const auto& v : m_adj[u])
                    {
                        double distance = v.second;
                        int vertex = v.first;
                        if(distance)
                            weight.emplace_back(distance);
                        if(distances[vertex] > distances[u] + distance)
                        {
                            distances[vertex] = distances[u] + distance;
                            pq.push({distances[vertex],vertex});
                        } 
                    } 
                     
                }
                std::cout << "\t     [Dijkstra algorithm]" << std::endl;
                for(size_t i = 2; i < m_vertices+1; ++i)
                    std::cout << i << "(" << weight[i] << ")" << "\t" << distances[i] << std::endl;
            }
            void DFSTraversal(size_t start = 1) const
            {
                static std::vector<bool> visited(m_vertices+1,false);
                if(!visited[start])
                {
                    visited[start] = 1;
                    std::cout << " " << start;
                    for(const auto& el : m_adj[start])
                        if(el.first)
                            if(!visited[el.first])
                                DFSTraversal(el.first);
                }
            }
            
            void BFSTraversal(size_t start = 1) const
            {
                std::vector<bool> visited(m_vertices+1,false);
                std::queue<unsigned> q;
                std::cout << std::endl;

                visited[start] = 1;
                q.emplace(start);
                while(!q.empty())
                {
                    start = q.front();
                    std::cout << start << " ";
                    q.pop();
                    for(const auto& el : m_adj[start])
                        if(el.first)
                            if(!visited[el.first] && (visited[el.first] = 1))
                                q.emplace(el.first);
                }
            }
            void printShortestPath2() const
            {
                std::vector<bool> mst(m_vertices+1,0);
                std::vector<int> distances(m_vertices+1,std::numeric_limits<int>::max());
                distances[1] = 0;
                for(size_t i = 1; i < m_vertices+1; ++i)
                {
                    int vertex = getMinimumVertex(mst,distances);
                    mst[vertex] = 1;

                    for(size_t j = 0; j < m_vertices; ++j)
                            if(!mst[j] && m_adj[vertex][j].second && distances[vertex] != std::numeric_limits<int>::max() && distances[vertex]+m_adj[vertex][j].second < distances[j])
                                distances[j] = distances[vertex] + m_adj[vertex][j].second;
                }
                std::cout << "\t     [Dijkstra's algorithm]" << std::endl;
                for(size_t i = 1; i < m_vertices+1; ++i)
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
            void printAdjacencyList(const bool& print = 1) const
            {
                if(print)
                    std::cout << "\t     [AdjacencyList]" << std::endl;
                else
                    std::cout << "\t     [MST Tree]" << std::endl;
                size_t i = 0,j = 0;
                for(const auto& v : m_adj)
                {
                    if(!j++)
                       continue;
                    std::cout << ++i << "|--";
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
            class min_priority_queue final
            {
                public:
                    min_priority_queue(const std::vector<double>& distances) : distance(distances), what(distances.size()), where(distances.size()) 
                    {
                        for(size_t i = 0; i < distance.size(); ++i)
                            what[i] = where[i] = i;
                    }
                    void decrease_key(const unsigned& i,const double& val)
                    {
                        distance[i] = val;
                        siftUp(where[i]);
                    }
                    size_t size() const
                    {
                        return what.size();
                    }
                    unsigned get_min()
                    {
                        unsigned result = what[0], i = 0, k = 2*i+2, n = what.size()-1;
                        what[0] = what[n];
                        what.pop_back();
                        while(k < n && distance[what[i]] > distance[what[k]] && distance[what[k-1]] > distance[what[k]] || --k < n && distance[what[i]] > distance[what[k]])
                        {
                            std::swap(what[i],what[k]);
                            where[what[i]] = i;
                            where[what[k]] = k;
                        }
                        return result;
                    } 
                    bool empty() const
                    {
                        return what.empty();
                    }
                private:
                    void siftUp(const unsigned& n)
                    {
                        unsigned i;
                        while(n > 0 && distance[what[i=(n-1)/2]] > distance[what[n]])
                        {
                            std::swap(what[i],what[n]);
                            where[what[i]] = i;
                            where[what[n]] = n;
                        }
                    }
                    std::vector<double> distance;
                    std::vector<int> what;
                    std::vector<int> where;
            };
            int getMinimumVertex(const std::vector<bool>& mst,const std::vector<int>& key) const
            {
                int min_key = std::numeric_limits<int>::max();
                int vertex = -1;
                for(size_t i = 0; i < m_vertices+1; ++i)
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
    graph.printMSTKruskal();
    graph.printMST(1);
    graph.printMSTPrim();
    graph.printShortestPath();
    std::cout << std::endl;
    //graph.printShortestPath2();
}
