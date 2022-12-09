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
#include <stack>

using namespace std;

class BitcoinNetwork {
    public:
        // Reads in the csv file and populates the adjacency list with the information within the file
        void createNetwork(string fileName);
        //return the number of nodes stored in the adjacency list
        size_t getSize();
        // Uses Djikstra's algorithm to find the shortest distance (most trustworthy path) between the start and end node
        int findSingleSourceShortestPathDistance(int start, int end);
        //Uses Djikstra's algorithm to find the shortest(most trustworthy) path between the start and end node
        vector<int> findSingleSourceShortestPath(int start, int end);
        //Uses Tarjan's algorithm to determine the number of strongly connected components in the bitcoin network
        int numberOfStronglyConnectedComponents();
    private:
        //map storing the adjacency list of the bitcoin network
        unordered_map<int, vector<pair<int, int>>> adjList_;
        vector<int> splitString(string row);
        //helper method used to find the shortest path 
        vector<unordered_map<int,int>> findSingleSourceShortestPathHelper(int start);
        //dept first search helper Method used to find number of strongly connected components
        void dfs(int node, stack<int>& st, unordered_map<int, bool>& onStackMap, unordered_map<int, int>& idMap, unordered_map<int, int>& lowMap, int& id, int& sccCount);
        // uses breadth first search to see if there is a path from the start node to the end node
        bool isValid(int start, int end);
        //used Bellman-Ford Algorithm to detect negative cycles, led us to change weights from -10 to 10, to 1 to 21 where 1 is the highest trustworthiness and 21 is the lowest trustworthiness
        bool hasNegativeCycle();
};