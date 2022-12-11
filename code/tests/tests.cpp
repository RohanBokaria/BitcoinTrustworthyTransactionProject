#include <catch2/catch_test_macros.hpp>
#include "BitcoinNetwork.h"

//Things that need to be tested
// Creation of the network
// isValid
// Single shortest path distance
// Single shortest path(with vertices)
// Strongly connected components

TEST_CASE("test_create_network") {
    BitcoinNetwork b;
    BitcoinNetwork b1;
    BitcoinNetwork b2;
    b.createNetwork("../../data/scc-simple.csv");
    b1.createNetwork("../../data/scc-complex.csv");
    b2.createNetwork("../../data/soc-sign-bitcoinotc.csv");
    REQUIRE(b.getSize() == 5);
    REQUIRE(b1.getSize() == 12);
    REQUIRE(b2.getSize() == 5881);
}
TEST_CASE("test_is_valid") {
    BitcoinNetwork b;
    BitcoinNetwork b1;
    b.createNetwork("../../data/scc-simple.csv");
    b1.createNetwork("../../data/scc-complex.csv");
    REQUIRE(b.isValid(0,6) == false);
    REQUIRE(b.isValid(4,1) == false);
    REQUIRE(b.isValid(1,4) == true);
    REQUIRE(b1.isValid(100, 200) == false);
    REQUIRE(b1.isValid(12, 1) == false);
    REQUIRE(b1.isValid(1, 12) == true);
}
TEST_CASE("test_strongly_connected_components") {
    BitcoinNetwork b;
    BitcoinNetwork b1;
    b.createNetwork("../../data/scc-simple.csv");
    b1.createNetwork("../../data/scc-complex.csv");
    REQUIRE(b.numberOfStronglyConnectedComponents() == 3);
    REQUIRE(b1.numberOfStronglyConnectedComponents() == 4);
}
TEST_CASE("test_dijkstra's - shortest path functions") {
    BitcoinNetwork b;
    BitcoinNetwork b1;
    b.createNetwork("../../data/scc-simple.csv");
    b1.createNetwork("../../data/scc-complex.csv");
    REQUIRE(b.findSingleSourceShortestPathDistance(2, 4) == 36);
    REQUIRE(b.findSingleSourceShortestPathDistance(3, 1) == INT_MAX);
    vector<int> v = {2, 1, 0, 3, 4};
    REQUIRE(b.findSingleSourceShortestPath(2, 4) == v);
    REQUIRE(b1.findSingleSourceShortestPathDistance(4, 7) == 8);
    REQUIRE(b1.findSingleSourceShortestPathDistance(1, 12) == 53);
    REQUIRE(b1.findSingleSourceShortestPathDistance(10, 4) == INT_MAX);
    vector<int> v1 = {4, 5, 7};
    vector<int> v2 = {1, 2, 4, 5, 7, 10, 11, 12};
    REQUIRE(b1.findSingleSourceShortestPath(4, 7) == v1);
    REQUIRE(b1.findSingleSourceShortestPath(1, 12) == v2);
}