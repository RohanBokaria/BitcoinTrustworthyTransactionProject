#include <catch2/catch_test_macros.hpp>
#include "BitcoinNetwork.h"

//Things that need to be tested
// Creation of the network
// Has negative cycle tests
// isValid
// Single shortest path distance
// Single shortest path(with vertices)
// Strongly connected components

TEST_CASE("test_create_network") {
    BitcoinNetwork b;
    BitcoinNetwork b1;
    b.createNetwork("../../data/test-ncycle.csv");
    b1.createNetwork("../../data/test-no-ncycle.csv");
    REQUIRE(b.getSize() == 8);
    REQUIRE(b1.getSize() == 7);

}

TEST_CASE("test_has_negative_cycle") {
    BitcoinNetwork b;
    BitcoinNetwork b1;
    b.createNetwork("../../data/test-ncycle.csv");
    b1.createNetwork("../../data/test-no-ncycle.csv");
    REQUIRE(b.hasNegativeCycle() == true);
    REQUIRE(b1.hasNegativeCycle() == false);
}


