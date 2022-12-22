#ifndef EDGE_H
#define EDGE_H

#include "Vertex.hpp"
#include "Graph.hpp"
#include <string>
#include <iostream>

class Vertex;

class Edge
{
    public:
    //Edge();
    //~Edge();
   /* void printEdge(){
        std::cout << "Position: " << position << " Weight: " << weight << " current: " << current->label << " adjacent: " << adjacent->label << std::endl;
    }*/

    private:
        unsigned long weight; 
        int position;
        
        //each edge has 2 vertices
        Vertex* current;//current vertex
        Vertex* adjacent; //adjacent vertex

    friend class Vertex;
    friend class Graph;
};

#endif