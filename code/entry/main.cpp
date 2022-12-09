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
}

