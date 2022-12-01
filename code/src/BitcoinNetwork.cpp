#include "BitcoinNetwork.h"
#include "Compare.h"

// Creates adjacency list based upon the data within the csv file
void BitcoinNetwork::createNetwork(string fileName) {
    ifstream ifs(fileName);
    for(string line; getline(ifs, line); line = "") {
        vector<int> splitRow = splitString(line);
        pair<int, int> p = make_pair(splitRow[1], splitRow[2]);
        adjList_[splitRow[0]].push_back(p);
        if(adjList_.count(splitRow[1]) == 0) {
            vector<pair<int,int>> v;
            adjList_[splitRow[1]] = v;
        }
    }
}
//Time Complexity: O(VE)
//Space Complexity: O(V)
bool BitcoinNetwork::hasNegativeCycle() {
    unordered_map<int, int> distanceMap;
    for(auto const& [key, value] : adjList_) {
        distanceMap[key] = INT_MAX;
    }
    distanceMap[1] = 0;
    
    for(size_t i = 0; i < adjList_.size() - 1; i++) {
        for(auto const& [vertex, edges] : adjList_) {
            int currWeight = distanceMap[vertex];
            for(auto const& edge : edges) {
                if(currWeight != INT_MAX && currWeight + edge.second < distanceMap[edge.first]) {
                    distanceMap[edge.first] = currWeight + edge.second;
                }
            }
        }
    }
    for(size_t i = 0; i < adjList_.size() - 1; i++) {
        for(auto const& [vertex, edges] : adjList_) {
            int currWeight = distanceMap[vertex];
            for(auto const& edge : edges) {
                if(currWeight != INT_MAX && currWeight + edge.second < distanceMap[edge.first]) {
                    return true;
                }
            }
        }
    }
    return false;
}
size_t BitcoinNetwork::getSize() {
    return adjList_.size();
}
//Checks if arguments provided to main are nodes and whether or not the end can be reached from the start
bool BitcoinNetwork::isValid(int start, int end) {
    if(adjList_.count(start) == 0 || adjList_.count(end) == 0) {
        return false;
    }
    if(start == end) {
        return true;
    }

    unordered_set<int> s;
    queue<int> q;
    q.push(start);
    s.insert(start);

    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        for(pair<int, int>& p : adjList_[curr]) {
            if(s.count(p.first) == 0) {
                if(p.first == end) {
                    return true;
                }
                s.insert(p.first);
                q.push(p.first);
            }
        }
    }
    return false;
}

vector<int> BitcoinNetwork::findSingleSourceShortestPath(int start, int end) {
    vector<unordered_map<int,int>> v = findSingleSourceShortestPathHelper(start);
    unordered_map<int,int>& distanceMap = v[0];
    unordered_map<int,int>& previousMap = v[1];
    vector<int> path;
    if(distanceMap[end] == INT_MAX) {
        return path;
    }
    int curr = end;
    while(curr != start) {
        path.push_back(curr);
        curr = previousMap[curr];
    }
    path.push_back(curr);
    reverse(path.begin(), path.end());
    return path;
}


vector<unordered_map<int,int>> BitcoinNetwork::findSingleSourceShortestPathHelper(int start) {
    unordered_map<int, int> distanceMap;
    unordered_map<int, bool> visitedMap;
    unordered_map<int, int> previousMap;
    for(auto const& [key, value] : adjList_) {
            distanceMap[key] = INT_MAX;
            visitedMap[key] = false;
    }
    distanceMap[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int,int>>, Compare> pq;
    pq.push({start, 0});
    while(!pq.empty()) {
        auto [node, distance] = pq.top();
        visitedMap[node] = true;
        pq.pop();
        if(distance > distanceMap[node]) continue;
        for(auto const& [neighbor, edgeWeight] : adjList_[node]) {
            if(visitedMap[neighbor]) continue;
            int newDistance = distanceMap[node] + edgeWeight;
            if(newDistance < distanceMap[neighbor]) {
                previousMap[neighbor] = node;
                distanceMap[neighbor] = newDistance;
                pq.push({neighbor, newDistance});
            }
        }
    }
    return {distanceMap, previousMap};
}

int BitcoinNetwork::findSingleSourceShortestPathDistance(int start, int end) {
    unordered_map<int, int> distanceMap;
    unordered_map<int, bool> visitedMap;
    
    for(auto const& [key, value] : adjList_) {
        distanceMap[key] = INT_MAX;
        visitedMap[key] = false;
    }
    distanceMap[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int,int>>, Compare> pq;
    pq.push({start, 0});
    while(!pq.empty()) {
        auto [node, distance] = pq.top();
        visitedMap[node] = true;
        pq.pop();
        if(distance > distanceMap[node]) continue;
        for(auto const& [neighbor, edgeWeight] : adjList_[node]) {
            if(visitedMap[neighbor]) continue;
            int newDistance = distanceMap[node] + edgeWeight;
            if(newDistance < distanceMap[neighbor]) {
                distanceMap[neighbor] = newDistance;
                pq.push({neighbor, newDistance});
            }
        }
        if(node == end) return distanceMap[node];
    }
    return INT_MAX;
}


unordered_map<int, double> BitcoinNetwork::calcBetweenessCentrality() {
    unordered_map<int, double> betweenessCentralityMap;
    vector<int> currPath;
    vector<vector<int>> allPaths;
    for(auto const& [start, edges] : adjList_) {
        if(betweenessCentralityMap.count(start) == 0) {
            betweenessCentralityMap[start];
        }
        unordered_map<int, unordered_set<int>> previousMap = betweenessCentralityHelper(start);
        for(auto const& [node, previousNodes] : previousMap) {
            currPath.push_back(node);
            dfs(node, start, currPath, allPaths, previousMap);
            for(vector<int> path : allPaths) {
                for(size_t i = 1; i < path.size() - 1; i++) {
                    betweenessCentralityMap[path[i]] += (double)1/(allPaths.size());
                }
            }
            currPath.clear();
            allPaths.clear();
    //         int numShortestPaths = previousNodes.size();
    //         for(int prev : previousNodes) {
    //             nextMap[prev].insert(node);
    //             if(prev != start) {
    //                 q.push(prev);
    //             }
    //         }
    //         while(!q.empty()) {
    //             int curr = q.front();
    //             q.pop();
    //             numShortestPaths += previousMap[curr].size() - 1;
    //             for(int previousNode : previousMap[curr]) {
    //                 nextMap[previousNode].insert(curr);
    //                 if(previousNode != start) {
    //                     q.push(previousNode);
    //                 }
    //             }
    //         }
    //         dfs(start, node, nextMap, freqMap);
    //         cout << "Start: " << start << ", End: " << node << endl;

    //         for(auto const& [key, value] : freqMap) {
    //             betweenessCentralityMap[key] += ((double)value/numShortestPaths);
    //             cout << key << ", " << betweenessCentralityMap[key] << endl;
    //         }
    //         // nextMap.clear();
    //         // freqMap.clear();
        }
    }
    return betweenessCentralityMap;
}

void BitcoinNetwork::dfs(int curr, int start, vector<int>& currPath, vector<vector<int>>& allPaths, const unordered_map<int, unordered_set<int>>& previousMap) {
    if(curr == start) {
        allPaths.push_back(currPath);
        return;
    }
    for(int previousNode : previousMap.at(curr)) {
        currPath.push_back(previousNode);
        dfs(previousNode, start, currPath, allPaths, previousMap);
        currPath.pop_back();
    }
}

unordered_map<int, unordered_set<int>> BitcoinNetwork::betweenessCentralityHelper(int start) {
    unordered_map<int, int> distanceMap;
    unordered_map<int, bool> visitedMap;
    unordered_map<int, unordered_set<int>> previousMap;
    for(auto const& [key, value] : adjList_) {
            distanceMap[key] = INT_MAX;
            visitedMap[key] = false;
    }
    distanceMap[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int,int>>, Compare> pq;
    pq.push({start, 0});
    while(!pq.empty()) {
        auto [node, distance] = pq.top();
        visitedMap[node] = true;
        pq.pop();
        if(distance > distanceMap[node]) continue;
        for(auto const& [neighbor, edgeWeight] : adjList_[node]) {
            if(visitedMap[neighbor]) continue;
            int newDistance = distanceMap[node] + edgeWeight;
            if(newDistance <= distanceMap[neighbor]) {
                if(newDistance < distanceMap[neighbor]) {
                    previousMap[neighbor].clear();
                }
                if(previousMap[neighbor].count(node) == 0) {
                    previousMap[neighbor].insert(node);
                    pq.push({neighbor, newDistance});
                }
                distanceMap[neighbor] = newDistance;
            }
        }
    }
    return previousMap;
}




// Finds the number of connected components using dfs algorithim each time a new node is encountered
// Time Complexity: O(n)
// Space Complexity: O(n)

// int BitcoinNetwork::numberOfConnectedComponents() {
//     int connectedComponents = 0;
//     unordered_set<int> visited;
//     for(auto const& [node, edges] : adjList_) {
//         if(visited.count(node) == 0) {
//             connectedComponents++;
//             dfs(node, visited);
//         }
//     }
//     return connectedComponents;
// } 

//helper method to parse csv data to create adjacency list for graph
vector<int> BitcoinNetwork::splitString(string row) {
    vector<int> result;
    int prev = 0;
    int currLength = 0;
    while(result.size() != 3) {
        for(size_t i = 0; i < row.size(); i++) {
            if(row[i] == ',') {
                string s = row.substr(prev, currLength);
                int convertedStr = stoi(s);
                result.push_back(convertedStr);
                prev = i + 1;
                currLength = 0;
            } else {
                currLength++;
            }
        }
    }
    result[2] = (result[2] * -1) + 11;
    return result;
}