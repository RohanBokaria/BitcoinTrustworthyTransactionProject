#include <unordered_map>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;
class BitcoinNetwork {
    public:
        void createNetwork(string fileName);
        size_t getSize();
        bool canReach(int start, int end);
        bool hasNegativeCycle();

    private:
        unordered_map<int, vector<pair<int, int>>> adjList_;
        vector<int> splitString(string row);
    
};
 