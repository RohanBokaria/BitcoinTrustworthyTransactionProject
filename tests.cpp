#include <catch2/catch_test_macros.hpp>
#include "BitcoinNetwork.h"


TEST_CASE("test_create_network") {
    BitcoinNetwork b;
    BitcoinNetwork b1;
    BitcoinNetwork b2;
    b.createNetwork("../../data/test-negatives.csv");
    b1.createNetwork("../../data/test-nonegatives.csv");
    b2.createNetwork("../../data/soc-sign-bitcoinotc.csv");
    REQUIRE(b.getSize() == 8);
    REQUIRE(b1.getSize() == 7);
    REQUIRE(b2.getSize() == 5881);

}
TEST_CASE("test_has_negative_cycle") {
    BitcoinNetwork b;
    BitcoinNetwork b1;
    b.createNetwork("../../data/test-nonegatives.csv");
    b1.createNetwork("../../data/test-negatives.csv");
    REQUIRE(b.hasNegativeCycle() == true);
    REQUIRE(b1.hasNegativeCycle() == false);
}
TEST_CASE("test_dijkstra's") {
    BitcoinNetwork b;
    BitcoinNetwork b1;
    b.createNetwork("../../data/simple-graph2.csv");
    REQUIRE(b.findSingleSourceShortestPathDistance(0, 6) == 20);
    REQUIRE(b.findSingleSourceShortestPathDistance(5, 1) == INT_MAX);
    vector<int> v = {0, 1, 4, 6};
    REQUIRE(b.findSingleSourceShortestPath(0, 6) == v);
}



