#include <iostream>
#include <thread> 
#include "BitcoinNetwork.h"
#include <time.h>
// void findDistance(BitcoinNetwork b, int start) {
//     cout << b.findSingleSourceShortestPathDistance(start) << endl;
// }
// thread th1(findDistance, b, startNode, endNode);
// th1.join();

int main(int argc, char* argv[]) {
    int start = clock();
    // if(argc < 3) {
    //     cout << "Invalid command line arguments!!!!" << endl;
    //     return 0;
    // }
    // int startNode = stoi(argv[1]);
    // int endNode = stoi(argv[2]);
    BitcoinNetwork b;
    b.createNetwork("../../data/soc-sign-bitcoinotc.csv");
    b.calcBetweenessCentrality();
    int end = clock();
    std::cout << "it took " << end - start << " ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << "seconds." << std::endl;
}

