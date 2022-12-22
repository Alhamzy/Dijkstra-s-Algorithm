#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include<iostream>
#include <vector>
#include "Edge.hpp"
#include "Graph.hpp"

class Edge;

class Vertex
{
    public:
       // Vertex();
       // ~Vertex();
        /*add edge - pair:(weight, adjacent vertex)*/
        void addVEdge (unsigned long w, Vertex *adj);
        //removes edge connecting a pair of vertices
        void removeVEdge(std::string v1, std::string v2);
        
         //utility functions 
        void labelVertex(std::string s);
        void positionV(int p);

       // void printEdges();

    private:
        int position;
        std::string label;
        std::vector<Edge*>edges;
        friend class Graph;
        friend class Edge;
       // friend class Graph;
};

#endif

