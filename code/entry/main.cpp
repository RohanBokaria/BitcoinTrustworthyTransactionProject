#include <iostream>
#include <thread> 
#include "BitcoinNetwork.h"
#include <time.h>

int main(int argc, char* argv[]) {
    int start = clock();
    if(argc < 3) {
        cout << "Invalid command line arguments!!!!" << endl;
        return 0;
    }
    int startNode = stoi(argv[1]);
    int endNode = stoi(argv[2]);
    BitcoinNetwork b;
    b.createNetwork("../../data/soc-sign-bitcoinotc.csv");
    cout << "Number of Strongly Connected Components: " << b.numberOfStronglyConnectedComponents() << endl;
    if (!b.isValid(startNode, endNode)) {
        cout << "No valid path between two users exists." << endl;
    }
    vector<int> path = b.findSingleSourceShortestPath(startNode, endNode);
    cout << "Shortest path between two users: ";
    for (size_t i = 0; i < path.size(); i++) {
        if (i != path.size() - 1) {
            cout << path[i] << " --> ";
        } else {
            cout << path[i] << endl;
        }
    }
    cout << "Distance of shortest path between two users: " << b.findSingleSourceShortestPathDistance(startNode, endNode) << endl;
}

