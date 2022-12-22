#include "Vertex.hpp"
#include "Edge.hpp"
//#include "Graph.hpp"

#include <string>
#include <iostream>
#include <list> 

void Vertex::labelVertex(std::string s)  { label = s; };

void Vertex:: positionV(int p){ position = p;};

//connect vertex  to adjacent vertex using edge with weight w 
 void Vertex::addVEdge (unsigned long w, Vertex *adj)
 {
     //using edges vector
     edges.push_back(new Edge);
     edges.back()->position = edges.size()-1;
     edges.back()->weight = w;
     edges.back()->current = this; //current vertex is this instantiation 
     edges.back()->adjacent = adj;

 }

void Vertex::removeVEdge(std::string v1, std::string v2) //x
{
 
    for(std::vector<Edge*>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        if((*it)->current->label == v1 && (*it)->adjacent->label == v2)
        {
            edges.erase(it);
            break;
        }
    }
}

