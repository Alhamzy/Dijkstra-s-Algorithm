#include "Graph.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include <algorithm>
#define MAX 100000

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#define INF 1000000

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

typedef std::pair<int,std::string> pqElem;//pair to hold variables in PQ


 unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
//map to check for visited nodes
    std::map<std::string, bool> visitedV;
    for(auto it = vertexlist.begin(); it != vertexlist.end(); ++it){
        visitedV.insert(std::make_pair((*it)->label, false));
    }


//map to store weight to each node    
    std::map<std::string, int> weightV;
    for(auto it = vertexlist.begin(); it != vertexlist.end(); ++it){
        weightV.insert(std::make_pair((*it)->label, INF));
    }

//map keeps track of prev nodes entering priority queue
    std::map<std::string,std::string> prevV;
    for(auto it = vertexlist.begin(); it != vertexlist.end(); ++it){
        weightV.insert(std::make_pair((*it)->label, INF));
    }

//PQ with (weight,label)
    std::priority_queue<pqElem,std::vector<pqElem>, std::greater<pqElem>> pq;


    
    
    //push intitial vertex, weight to itself, mark as visited
    pq.push(pqElem(0,startLabel));//starting node now in priority queue (index,weight)
    weightV[startLabel]=0;//update weight of startLabel in array

    while(pq.size() != 0){//while PQ is not empty
        //variables to hold data extracted from PQ
        std::string index=NULL;
        int minWeight=0;
        index, minWeight=Q.top;//grab first index and weight from pq to search adj nodes
        pq.pop();//remove from PQ        

        if(weightV[index]<minWeight){
            continue;
        } //skip nodes with weight more than weight in array

        //iterator to find adjacent nodes
        for(auto  s= vertexlist.begin(); s!=vertexlist.end(); s++)
        {
        if((*s)->label == startLabel)
        {
            auto it = *s;
        }
        }
        
        for(auto it = edges.begin(); it != edges.end(); ++it){//move through edge list for corresponding index(vertex)
            if(visitedV[(*it)->adjacent->label]=true) continue;//skip adjacent edges that have been already visited

            std::string adjIndex = ((*it)->adjacent->label);
            int edgeW = ((*it)->current->w);


            int newW = weightV[index] + edgeW;//new found weight to adjacent vertex
            //compare new found weight to weight vector, to check relaxation is necessary
            if(newW < weightV[adjIndex]){
            weightV[adjIndex] = newW;//new weight for relaxed vertex
            prevV[adjIndex] = index;//store relaxed vertex
            Q.push((adjIndex,newW));//add to PQ to check next
            visitedV[index]=true;
            }
        }
    }


    //updating path vector to store sequence
     std::string::iterator it;
     while((weightV[endLabel] != INF) && it != NULL){
            it = endLabel;
            path.insert(*it);
            it= prevV[(*it)]; 
    }
    path.reverse(path.begin(), path.end());
   return weightV[endLabel];//return weight to end vertex

}
