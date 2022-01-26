#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <regex>
#include <queue>

#include "graph.h"
#include "graphparse.h"


int main(int argc, char* argv[]){

    std::string filename = "";
    switch(argc){
        case 1:
            std::cout << "Error: no input file\n";
            return 0;
            break;

        case 2 :
            filename = argv[argc-1];
            break;
    }

    

    Graph g;
    createGraph(g, filename);
   

    
    return 0;
}