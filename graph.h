#pragma once

#include <vector>
#include <utility>
#include <cstdint>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <queue>

namespace arcade {


    template <typename T = uint8_t>
    struct Node{
        T data;
        uint8_t ID;
        inline Node(){ data = 0; }
        inline Node(T d) : data(d) {};

        std::vector<Node<T>*> connections;
    };

    template <typename T = uint8_t>
    struct Edge {
        Node<T>* n1 = nullptr;
        Node<T>* n2 = nullptr;
        uint8_t weight = 0;

        inline Edge(Node<T>* _n1, Node<T>* _n2) 
        : n1(_n1), n2(_n2) {}
    };

    template <typename T = uint8_t>
    using GraphSet = std::pair<std::vector<Node<T>*>, std::vector<Edge<T>*>>;
                // ADJLIST =  SET ( NODEID, SET ( NODEID, WEIGHT ))
    using AdjList = std::vector<std::pair<char, std::vector<std::pair<char, char>>>>;
    using AdjLine = std::pair<char, std::vector<std::pair<char, char>>>;

    // Graph -  G {V, E}
    template <typename T>
    struct Graph{

        GraphSet<int> set;
        uint8_t nodecount = 0;
        
        inline void addNode(){
            Node<T> n; n.ID = nodecount;
            set.first.push_back(n);
            nodecount++;
            return;
        }
        inline void addNode(const uint8_t ID){
            Node<T> n; n.ID = ID;
            set.first.push_back(n);
            nodecount++;
            return;
        }

        inline void connect(Node<T>* _n1, Node<T>* _n2){
            Edge<T> e (*& _n1, *& _n2);
            set.second.push_back(e);
            return;
        }
        inline void connect(const std::string _n1, const std::string _n2){
            connect(findNode(_n1), findNode(_n2));
        }
        inline void disconnect(Node<T>* _n1, Node<T>* _n2){
            for (int i = 0; i < set.second.size(); i++){
                if (_n1 == set.second[i]->n1 && _n2 == set.second[i]->n2)
                    set.second.erase(set.second.begin()+i);
            }
            return;
        }

        inline bool doesNodeExist(std::string n){
            for (auto &i : set.first){
                if (std::to_string(i->ID) == n){
                    return true;
                }
            }
            return false;
        }

        inline void disconnect(std::string _n1, std::string _n2){
            disconnect(findNode(_n1), findNode(_n2));
        }
        inline Node<T>* findNode(std::string _n){
            for (auto &i : set.first)
                if (i->ID == std::stoi(_n))
                    return i;
        }
        inline Edge<T>* findEdge(std::string _n1, std::string _n2){
            for (auto &i : set.second)
            {
                if (i->n1->ID == findNode(_n1)->ID && i->n2->ID == findNode(_n2)->ID){
                    return &i;
                }
            }
        }
    };

    template <typename T = uint8_t>
    inline AdjList createAdjList(Graph<T> & graph, const std::string f){

        int ncount = 0;
        const std::regex match("\\d, \\d");
        // nodeID : targetnode, weight

        AdjList l;
        std::string line = "";
        std::ifstream file;
        file.open(f);
        while(std::getline(file, line))
        {
            std::size_t pos = line.find(":");
            std::string nodeID = line.substr(0, pos);

            std::queue<std::string> queue;
            std::smatch results;
            std::string capture = "";
            std::regex_token_iterator<std::string::iterator> rend;
            std::regex_token_iterator<std::string::iterator> a (line.begin(), line.end(), match);

            while (a != rend){
                queue.push(*a++);
            }

            AdjLine adjline;
            adjline.first = *nodeID.c_str();

            while (!queue.empty()) {
                std::string elementcapture = queue.front();
                queue.pop();
                std::size_t first = elementcapture.find(",");
                std::string targetnode = elementcapture.substr(0, first);
                std::string targetweight = elementcapture.substr(first+1, elementcapture.size());
                std::pair<char, char> adjpair(*targetnode.c_str(), *targetweight.c_str());
                adjline.second.emplace_back(adjpair.first, adjpair.second);
            }
            l.push_back(adjline);
        }
        l.erase(l.end());
        return l;
    }

    template <typename T = uint8_t>
    inline void createGraph(Graph<T> & graph, const std::string f){
        AdjList adjlist = createAdjList(graph, f);
        int iterator = 0;

        for (auto &i : adjlist){
            graph.addNode(graph.nodecount);
            iterator++;
            for (auto &j : i.second){
                if (j.first != graph.doesNodeExist(std::to_string(j.first))){
                    int tempID = j.first - '0';
                    graph.addNode(tempID);
                }
                int tempID = j.first - '0';
                int tempWeight = j.second - '0';
                graph.connect(std::to_string(iterator-1), std::to_string(tempID));
                graph.findEdge(std::to_string(iterator-1), std::to_string(tempID))->weight = tempWeight;
            }
        }
    }
}