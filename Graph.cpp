#include "Graph.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include <algorithm>
#define MAX 100000

#include <iostream>
#include <string>
#include <vector>

void Graph::addVertex(std::string label) //adding vertices to back of vector
{
    int pos = vertexlist.size(); //position of new vertex would be last slot in vector 
    
    vertexlist.push_back(new Vertex); //new vertex object pushed to back of vertex list vector
    vertexlist.back()->labelVertex(label); //last element is the one just pushed - assign label
    vertexlist.back()->positionV(pos); //assign vertex position


}

void Graph::removeVertex(std::string label) //using iterators
{
   int removedpos;
    //iterating through vertexlist to find matching vertex label
     for(std::vector<Vertex*>::iterator it = vertexlist.begin(); it != vertexlist.end(); ++it)
    {
        if((*it)->label == label)
        {
            removedpos = (*it)->position;
            vertexlist.erase(it);
            break;
        }

    }
    //remaining vertices need to be shifted upwards after the deletion 
    for(std::vector<Vertex*>::iterator it2 = vertexlist.begin(); it2 != vertexlist.end(); ++it2)
    {
        //if the vertex is after the one removed then shift up 
        if((*it2)->position >= removedpos)
        {
            (*it2)->position -= 1;
        }
    }

}

 void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
 {
     int pos1, pos2;

    for(std::vector<Vertex*>::iterator it = vertexlist.begin(); it != vertexlist.end(); ++it)
    {
         //loacting vertex with label1
        if((*it)->label == label1)
        {
            pos1 = (*it)->position;
        }
        
         //locating vertex with label2 (adjacent vertex)
        if((*it)->label == label2)
        {
            pos2 = (*it)->position;
        }

    }
      //adding weighted edge between vertex and adjacent vertex
        vertexlist.at(pos1)->addVEdge(weight, vertexlist.at(pos2));
        vertexlist.at(pos2)->addVEdge(weight, vertexlist.at(pos1));

 }


 void Graph::removeEdge(std::string label1, std::string label2)
 {
     int pos1, pos2;
     //iterating through vertex list to find vertex and its adjacent vertex
     
    
       for(std::vector<Vertex*>::iterator it = vertexlist.begin(); it != vertexlist.end(); ++it)
       { //loacting vertex with label1
          if((*it)->label == label1)
           {
                pos1 = (*it)->position;
           }
           break;
       }
       vertexlist.at(pos1)->removeVEdge(label1, label2);  //remove vertex
        
       //remove adjacent vertex 
       for(std::vector<Vertex*>::iterator it = vertexlist.begin(); it != vertexlist.end(); ++it)
       { //loacting vertex with label2
          if((*it)->label == label2)
           {
                pos2 = (*it)->position;
           }
           break;
       }
       vertexlist.at(pos2)->removeVEdge(label2, label1);

    
 }



 unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path)
 {
    unsigned long shortest = MAX;
    unsigned int V = vertexlist.size();

    std::vector<unsigned long> distance(V, MAX); //vector of distances between vertices
    std::vector<Vertex*> unvisited; //unvisted vertices
    std::vector<Vertex*> previous(V, NULL);
    Vertex* start;
    Vertex* end;

    //populating vector with unvisited nodes
    for(std::vector<Vertex*>::iterator i= vertexlist.begin(); i!=vertexlist.end();i++)
    {    unvisited.push_back(*i); }
    
    //find start node
    int Sindex =0;
    for(std::vector<Vertex*>::iterator s= vertexlist.begin(); s!=vertexlist.end(); s++)
    {
        if((*s)->label == startLabel)
        {
            start = *s;
            distance[Sindex] = 0;

            break;
        }
      
        Sindex++;
    }


    for(std::vector<Vertex*>::iterator e= vertexlist.begin(); e!=vertexlist.end(); e++)
    {
        if((*e)->label == endLabel)
        {
            end = *e;
            break;
        }
       
    }

    //loop till vector is empty
    while(unvisited.size() !=0)
    {
        int minIndex = 0 ;
        for (unsigned int i = 0; i<unvisited.size(); i++)
        {
            //compare to get nearer node 
            if(distance[unvisited[i]->position] < distance[start->position] )
            {
                start = unvisited[i]; //assigns the closer node as the current vertex
                minIndex = i;
            }
        }

        //if end of list reached (all nodes visited) - and minimum path is found, push the sequence to path vector
        if(start == end)
        {
            //add previous vertices of current node to  path list 
            path.push_back(end->label);
            Vertex* min = end; 
            //starting from the end (minimum) until there are no more previous nodes
            while(previous[min->position]!= NULL)
            {
                path.push_back(previous[min->position]->label);
                min = previous[min->position];//moving to previous node
            }

            //reverse to correct order since the end vertex was placed first
            reverse(path.begin(), path.end());

            shortest = distance[start->position]; 
            break;
        }
        //erase vertex from unvisited list once visited
        unvisited.erase(unvisited.begin()+minIndex); //erase current node - only allows iterator argument
        
        //checking adjacent vertices of the visited vertex(start) - loop ends once it has checked all the connected edges 
        for (unsigned int i=0; i< start->edges.size();i++)
        {
            unsigned int totalDistance = distance[start->position] + start->edges[i]->weight; 
            //edge relaxation
            //if distance between current vertex and an adjacent one is less than the vertex and neighbouring adjacent vertex
            if(totalDistance < distance[start->edges[i]->adjacent->position])
            {
                distance[start->edges[i]->adjacent->position] = totalDistance;  
                previous[start->edges[i]->adjacent->position] = start;
            }
        }
        //Move to next vertex
        if(unvisited.size()!=0)
            start = unvisited[0];

    }
     return shortest;
 }
