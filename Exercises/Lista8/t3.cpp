#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

namespace ASD
{
    class Graph final
    {
        private:
            struct Edge;
        public:
            explicit Graph(const size_t& num = 10) : m_vertices(num),m_adj(num) {}
            void createGraph(const std::string& filename)
            {
                std::ifstream inFile;
                inFile.open(filename);
                inFile >> m_vertices >> m_edges;
                m_adj.resize(m_vertices);
                if(inFile.is_open())
                {
                    Edge edge;
                    while(!inFile.eof() && inFile >> edge.m_src && inFile >> edge.m_dest && inFile >> edge.m_distance)
                        addEdge(edge);
                }
                inFile.close();
            }
            void printAdjacencyMatrix()
            {
                for(size_t i = 0; i < m_adj.size(); ++i)
                {
                    for(const auto& l : m_adj)
                        if(m_adj[i] == l)
                        {
                            const auto& el = l.begin();
                            std::cout << (*el).second << " ";
                        }
                        else
                            std::cout << 0 << " ";
                    std::cout << std::endl;
                }
            }
            void printMST();
            void printShortestPath();
            void edge2(const size_t& src,const size_t& dest,const double& distance = 1)
            {
                m_adj[src].push_back({dest,distance});
                m_adj[dest].push_back({src,distance});
            }
            void addEdge(const Edge& edge)
            {
                m_adj[edge.m_src].push_back({edge.m_dest,edge.m_distance});
                m_adj[edge.m_dest].push_back({edge.m_src,edge.m_distance});
            }
            size_t getNumberOfEdges() const
            {
                return m_edges;
            }
            size_t getNumberOfVertices() const
            {
                return m_vertices;
            }
            void show() const
            {
                size_t i = 0;
                for(const auto& l : m_adj)
                {
                    std::cout << i++ << "|--";
                    for(const auto& n : l)
                        std::cout << n.second << "-->" << n.first << "|--";
                    std::cout << std::endl;
                }
            }
        private:
            struct Edge final
            {
                size_t m_src = 0;
                size_t m_dest = 0;
                size_t m_distance = 0;
            };
            std::vector<std::list<std::pair<size_t,double>>> m_adj;
            size_t m_vertices;
            size_t m_edges;
    };
}

int main()
{
    ASD::Graph graph;
    graph.createGraph("t3txt.txt");
    std::cout << graph.getNumberOfVertices() <<  "," << graph.getNumberOfEdges() << std::endl;
    graph.show();
    graph.printAdjacencyMatrix();
}
