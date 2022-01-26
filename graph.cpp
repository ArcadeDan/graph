#include "graph.h"



void Graph::addNode(){

    Node node;
    node.nodeID = nodecount;
    set.first.push_back(node);
    nodecount++;
}

Node* Graph::findNode(std::string n){
    for (auto &i : set.first){
        if (i.nodeID == std::stoi(n)){
            return &i;
        }
    }
}

void Graph::connect(Node* n1, Node* n2){
    Edge edge(*&n1, *&n2);
    set.second.push_back(edge);
}

void Graph::connect(std::string n1, std::string n2){
    connect(findNode(n1), findNode(n2));
}

void Graph::disconnect(Node* n1, Node* n2){
    for (int i = 0; i < set.second.size(); i++ ){
        if (n1 == set.second[i].n1 && n2 == set.second[i].n2){
            set.second.erase(set.second.begin()+i);
        }
        
    }
}

void Graph::addNode(int ID){
    Node node;
    node.nodeID = ID;
    set.first.push_back(node);
    nodecount++;
}

void Graph::disconnect(std::string n1, std::string n2){
    disconnect(findNode(n1), findNode(n2));
}

bool Graph::doesNodeExist(std::string n){
    for (auto &i : set.first){
        if (std::to_string(i.nodeID) == n){
            return true;
        }
    }
    return false;
}

Edge* Graph::findEdge(std::string n1, std::string n2){
    for (auto &i : set.second){
        if (i.n1->nodeID == findNode(n1)->nodeID && i.n2->nodeID == findNode(n2)->nodeID){
            return &i;
        }
    }
}