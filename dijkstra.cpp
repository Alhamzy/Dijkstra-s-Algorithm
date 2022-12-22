#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <string>
#include <iterator>
#include <map>
#define INF 1000000

typedef std::pair<int,std::string> pqElem;//pair to hold variables in PQ


unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
//map to check for visited nodes
    std::map<std::string, bool> visitedV;
    for(auto it = vertexlist.begin(); it != vertexlist.end(); ++it){
        visitedV.insert(std::pair((*it)->label, false));
    }


//map to store weight to each node    
    std::map<std::string, int> weightV;
    for(auto it = vertexlist.begin(); it != vertexlist.end(); ++it){
        weightV.insert(std::pair((*it)->label, INF));
    }

//map keeps track of prev nodes entering priority queue
    std::map<std::string, int> prevV;
    for(auto it = vertexlist.begin(); it != vertexlist.end(); ++it){
        weightV.insert(std::pair((*it)->label, INF));
    }

//PQ with (weight,label)
    std::priority_queue<pqElem,std::vector<pqElem>, std::greater<pqElem>> pq;


    
    
    //push intitial vertex, weight to itself, mark as visited
    pq.push(pqElem(0,startLabel));//starting node now in priority queue (index,weight)
    weightV[startLabel]=0;//update weight of startLabel in array

    while(pq.size != 0){//while PQ is not empty
        //variables to hold data extracted from PQ
        std::string index=NULL;
        int minWeight=0;
        index, minWeight=Q.top;//grab first index and weight from pq to search adj nodes
        pq.pop;//remove from PQ        

        if(weight[index]<minWeight){
            continue;
        } //skip nodes with weight more than weight in array

        //iterator to find adjacent nodes
        for(auto it = edges.begin(); it != edges.end(); ++it){//move through edge list for corresponding index(vertex)
            if(visitedV[(*it)->adjacent->label]=true) continue;//skip adjacent edges that have been already visited

            std::string adjIndex = ((*it)->adjacent->label);
            int edgeW = ((*it)->current->w);


            int newW = weightN[index] + edgeW;//new found weight to adjacent vertex
            //compare new found weight to weight vector, to check relaxation is necessary
            if(newW < weightN[adjIndex]){
            weightV[adjIndex] = newW;//new weight for relaxed vertex
            prevV[adjIndex] = index;//store relaxed vertex
            Q.push((adjIndex,newW));//add to PQ to check next
            visitedV[index]=true;
            }
        }
    }

/*
    //updating path vector to store sequence
     std::string::iterator it;
     while((weightN[endLabel] != INF) && it != NULL){
            it = endLabel;
            path.insert(*it);
            it= currentNode[it]; 
    }
    path.reverse;*/
   return weightN[endLabel];//return weight to end vertex

}
