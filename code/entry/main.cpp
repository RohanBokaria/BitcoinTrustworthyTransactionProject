#include <iostream> 
#include "BitcoinNetwork.h"
int main(int argc, char* argv[]) {
    // if(argc < 3) {
    //     cout << "Invalid command line arguments!!!!" << endl;
    //     return 0;
    // }
    // int startNode = stoi(argv[1]);
    // int endNode = stoi(argv[2]);

    BitcoinNetwork b;
    b.createNetwork("../../data/soc-sign-bitcoinotc.csv");
    cout << b.hasNegativeCycle() << endl;


    // bool canReach = b.canReach(startNode, endNode);
    // if(canReach) {
    //     cout << "You can make a transaction between these two individuals!!" << endl;
    // } else {
    //     cout << "Can not make a transaction between these two individuals!!!" << endl;
    // }
}