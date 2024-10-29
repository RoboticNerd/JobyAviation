#include <catch2/catch_test_macros.hpp>
#include "classes.h"

// ============== PASSENGER GROUP =====================================

TEST_CASE("PassengerGroup - create passengers", "[PassengerGroup]") {
    PassengerGroup ppp1;                                        // lets make some passenger groups
    PassengerGroup ppp2;    
    ppp1.createPassengers(3,18);                                // lets create some passengers
    ppp2.createPassengers(5,18);    

    REQUIRE(ppp1.size() <= 3);                                  // now lets make sure sizes make sense
    REQUIRE(ppp1.size() > 0);
    REQUIRE(ppp2.size() <= 5);
    REQUIRE(ppp2.size() > 0);
}

TEST_CASE("PassengerGroup - distance", "[PassengerGroup]") {
    PassengerGroup ppp1;
    PassengerGroup ppp2;
    ppp1.createPassengers(3,18);
    ppp2.createPassengers(5,12);

    REQUIRE(ppp1.destination_distance <= 18);
    REQUIRE(ppp2.destination_distance <= 12);
}


