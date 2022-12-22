#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include <vector>
#include <string>

class Vertex;
class Graph:public GraphBase
{
    public:
        Graph() {};
        //given functions
        void addVertex(std::string label);
        void removeVertex(std::string label);
        void addEdge(std::string label1, std::string label2, unsigned long weight);
        void removeEdge(std::string label1, std::string label2);
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);   


    private:
        
        std::vector<Vertex*>vertexlist; 
       
    
};


#endif