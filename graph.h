#pragma once

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <queue>


struct Node{
    int nodeID = 0;
    Node() : nodeID(0) {}
    Node(int n) : nodeID(n) {} 
};

struct Edge{
    int weight = 0;
    Node* n1 = nullptr;
    Node* n2 = nullptr;

    Edge(Node* n1, Node* n2) : n1(n1), n2(n2){}
};

struct Graph{

    int nodecount = 0;
    std::pair<std::vector<Node>, std::vector<Edge>> set;
    bool doesNodeExist(std::string n);
    void addNode();
    void addNode(int ID);
    void connect(Node* n1, Node* n2);
    void connect(std::string n1, std::string n2);
    void disconnect(Node* n1, Node* n2);
    void disconnect(std::string n1, std::string n2);
    Node* findNode(std::string n);
    Edge* findEdge(std::string n1, std::string n2);
};



