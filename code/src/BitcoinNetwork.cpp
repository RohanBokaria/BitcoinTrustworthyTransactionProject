#include "BitcoinNetwork.h"


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
//O(VE)
bool BitcoinNetwork::hasNegativeCycle() {
    unordered_map<int, int> distanceMap;
    for(auto const& [key, value] : adjList_) {
        distanceMap[key] = INT_MAX;
    }
    distanceMap[1] = 0;

    for(size_t i = 0; i < adjList_.size() - 1; i ++) {
        for(auto const& [vertex, edges] : adjList_) {
            int currWeight = distanceMap[vertex];
            if(currWeight != INT_MAX) {
                for(auto const& edge : edges) {
                    if(currWeight + edge.second < distanceMap[edge.first]) {
                        distanceMap[edge.first] = currWeight + edge.second;
                    }
                }
            }
        }
    }
    for(size_t i = 0; i < adjList_.size() - 1; i++) {
        for(auto const& [vertex, edges] : adjList_) {
            int currWeight = distanceMap[vertex];
            if(currWeight != INT_MAX) {
                for(auto const& edge : edges) {
                    if(currWeight + edge.second < distanceMap[edge.first]) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

size_t BitcoinNetwork::getSize() {
    return adjList_.size();
}

bool BitcoinNetwork::canReach(int start, int end) {
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
    return result;
}
