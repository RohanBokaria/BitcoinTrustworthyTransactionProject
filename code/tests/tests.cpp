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
    b.createNetwork("../../data/scc-simple.csv");
    b1.createNetwork("../../data/scc-complex.csv");
    REQUIRE(b.getSize() == 5);
    REQUIRE(b1.getSize() == 12);
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


