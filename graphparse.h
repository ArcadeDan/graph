#pragma once


#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <queue>

#include "graph.h"

inline std::vector<std::pair<char, std::vector<std::pair<char, char>>>> createAdjList(Graph & graph, std::string f){

    int nodecount = 0;
    const std::regex match("\\d,\\d");
    // nodeID : targetednode, weight
    std::vector<std::pair<char, std::vector<std::pair<char, char>>>> adjlist;
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

        std::pair<char, std::vector<std::pair<char, char>>> adjline;
        adjline.first = *nodeID.c_str();
        while (!queue.empty()){
            std::string elementcapture = queue.front();
            queue.pop();
            std::size_t first = elementcapture.find(",");
            std::string targetnode = elementcapture.substr(0, first);
            std::string targetweight = elementcapture.substr(first+1, elementcapture.size());
            std::pair<char, char> adjpair(*targetnode.c_str(), *targetweight.c_str());
            adjline.second.emplace_back(adjpair.first, adjpair.second);
        }


        adjlist.push_back(adjline);
        /*
        while (a != rend){
            std::cout << *a++ << " ";
            
        }
        std::cout << "\n";
        */
       
    }
    adjlist.erase(adjlist.end());
    return adjlist;
    
}

inline void createGraph(Graph & graph, std::string f){
    std::vector<std::pair<char, std::vector<std::pair<char, char>>>> adjlist = createAdjList(graph, f);

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