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

int BitcoinNetwork::numberOfStronglyConnectedComponents() {
    int id = 0;
    int sccCount = 0;
    unordered_map<int, int> idMap;
    unordered_map<int, int> lowMap;
    unordered_map<int, bool> onStackMap;
    stack<int> st;
    for(auto const& [node, neighbors] : adjList_) {
        idMap[node] = -1;
        lowMap[node];
        onStackMap[node];
    }
    for(auto const& [node, neighbors] : adjList_){
        if(idMap[node] == -1) {
            dfs(node, st, onStackMap, idMap, lowMap, id, sccCount);
        }
    }
    return sccCount;
}
void BitcoinNetwork::dfs(int node, stack<int>& st, unordered_map<int, bool>& onStackMap, unordered_map<int, int>& idMap, unordered_map<int, int>& lowMap, int& id, int& sccCount) {
    st.push(node);
    onStackMap[node] = true;
    idMap[node] = lowMap[node] = id++;

    for(auto const& [neighbor, edgeWeight] : adjList_[node]) {
        if(idMap[neighbor] == -1) dfs(neighbor, st, onStackMap, idMap, lowMap, id, sccCount);
        if(onStackMap[neighbor]) lowMap[node] = min(lowMap[node], lowMap[neighbor]);
    }
    if(idMap[node] == lowMap[node]) {
        int currNode = st.top();
        st.pop();
        while(currNode != node) {
            onStackMap[currNode] = false;
            lowMap[currNode] = idMap[node];
            currNode = st.top();
            st.pop();
        }
        onStackMap[node] = false;
        lowMap[node] = idMap[node];
        sccCount++;
    }
}

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