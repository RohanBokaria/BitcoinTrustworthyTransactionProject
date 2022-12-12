# Results of Each Algorithm:

# Djikstra's Algorithm:

int findSingleSourceShortestPathDistance(int start, int end) {}
        
- find the shortest distance (most trustworthy path) bewteen the start and end node
            
            
vector<int> findSingleSourceShortestPath(int start, int end) {}
        
- find the shortest (most trustworthy) path between the start and end node
        
Tested both of these functions in TEST_CASE("test_dijkstra's - shortest path functions")
- Passed all assertions and correctly outputted the right path and distance on basic csv files.  
        
 # Tarjan's Algorithm:

 int numberOfStronglyConnectedComponents()
        
 - determine the number of strongly connected components in the bitcoin network
        
 Tested this function in TEST_CASE("test_strongly_connected_components")
 - Passed all assertions and correctly outputted the right number of strongly connected components on basic csv files
            
# Breadth First Search:
 
bool isValid(int start, int end)
        
- uses breadth first search to see if there is a path from the start node to the end node
        
Tested this function in TEST_CASE("test_is_valid")
- Passed all assertions and correctly determined if two nodes had a valid path between them on basic csv files

        
# Leading Question:
- Our original leading question was: given a start bitcoin user and an end user, we want to see if a path between them is possible. And if so, find a path based upon various constraints. We were able to successfully determine if a path between two users was possible, which was implemented in our isValid() function using BFS algorithm. Regarding the next part of our question of finding a path with various constraints, we were able to successfully do this with our only constraint being the shortest path based on trustworthiness. We used Dijkstra's algorithm, which is used to find the shortest path between two nodes in a graph. Using our findSingleSourceShortestPathDistance() function, one can see the trustworthiness between two users and ultimately decide if a user is worthy of doing a transaction with. One of our orignial goals was to find the number of strongly connected components witinin the network. We were able to effectively able to do this by implementing Tarjan's algorithm. 
