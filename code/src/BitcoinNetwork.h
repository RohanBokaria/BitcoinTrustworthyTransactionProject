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
        bool isValid(int start, int end);
        bool hasNegativeCycle();
        int findSingleSourceShortestPathDistance(int start, int end);
        vector<int> findSingleSourceShortestPath(int start, int end);
        //Simple dfs doesn't work for directed graphs
        int numberOfConnectedComponents();
        //use helper function for every node in map and then calculate betweeness centrality?
        //modify djikstra to work with <= to, if less than clear whatever is there and if = add it into the previous map
        unordered_map<int, double> calcBetweenessCentrality();
        unordered_map<int, unordered_set<int>> betweenessCentralityHelper(int start);

    private:
        unordered_map<int, vector<pair<int, int>>> adjList_;
        vector<int> splitString(string row);
        //Can change this to only return the previousMap if the distance is not INT_MAX
        vector<unordered_map<int,int>> findSingleSourceShortestPathHelper(int start);
        void dfs(int curr, int start, vector<int>& currPath, vector<vector<int>>& allPaths, const unordered_map<int, unordered_set<int>>& previousMap);
};