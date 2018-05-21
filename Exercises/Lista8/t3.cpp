#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <forward_list>
#include <string>

namespace ASD
{
    class UnionFind final
    {
        
    };
    class Graph final
    {
        private:
            struct Edge;
        public:
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
                
            }
            void printShortestPath();
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
                size_t m_src = 0;
                size_t m_dest = 0;
                double m_distance = 0;
            };
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
}
