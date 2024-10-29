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


// ============== VEHICLE =====================================

TEST_CASE("Vehicle - loading vehicle stats correctly", "[Vehicle]") {
    Vehicle vvv0(0);                                            // load up all 5 vehicles
    Vehicle vvv1(1);
    Vehicle vvv2(2);
    Vehicle vvv3(3);
    Vehicle vvv4(4);

    REQUIRE(vvv0.company == "alpha");                           // check a few stats
    REQUIRE(vvv1.cruise_speed >= 160);
    REQUIRE(vvv2.battery_capacity == 220);
    REQUIRE(vvv3.time_to_charge == 37.2);
    REQUIRE(vvv4.energy_consumed_cruise >= 3.6);
}

TEST_CASE("Vehicle - load passengers", "[Vehicle]") {
    Vehicle vvv0(0);                                            // start single vehicle sim
    vvv0.moveOneMin();
    vvv0.moveOneMin();
    vvv0.moveOneMin();
    REQUIRE(vvv0.vehicle_state > 1);                            // check some passenger stats
    REQUIRE(vvv0.vehicle_passengers.size() > 0);
    REQUIRE(vvv0.vehicle_passengers.size() <= vvv0.max_passengers);
}

TEST_CASE("Vehicle - reduce battery during flight", "[Vehicle]") {
    Vehicle vvv0(0);                                            // start single vehicle sim
    vvv0.moveOneMin();
    vvv0.moveOneMin();
    vvv0.moveOneMin();
    REQUIRE(vvv0.battery_charge < vvv0.battery_capacity);       // check some battery stats
    REQUIRE(vvv0.battery_charge > vvv0.battery_capacity*.8);
}

TEST_CASE("Vehicle - increasing distances during flight", "[Vehicle]") {
    Vehicle vvv0(0);                                            // start single vehicle sim
    vvv0.moveOneMin();
    vvv0.moveOneMin();
    vvv0.moveOneMin();
    REQUIRE(vvv0.flight_distance > 0);                          // check vehicle/pass distance stats
    REQUIRE(vvv0.vehicle_passengers.destination_distance < vvv0.distance_to_airport);
}

TEST_CASE("Vehicle - battery can be depleated", "[Vehicle]") {
    Vehicle vvv0(0);                                            // run single vehicle sim for long time
    for (int i = 0; i<1000 ; i++) {
	    vvv0.moveOneMin();
    }                                                           
    vvv0.print();                                               // check to make sure stats make sense
    REQUIRE(vvv0.battery_charge <= vvv0.energy_consumed_cruise*32);                         
    REQUIRE(vvv0.vehicle_state == 5);
    REQUIRE(vvv0.passengerKm < vvv0.max_passengers*vvv0.flight_distance);
}

TEST_CASE("Vehicle - battery charges and vehicle doesn't move during charging", "[Vehicle]") {
    Vehicle vvv0(0);                                            // create vehicle
    vvv0.battery_charge = 0;                                    // kill battery SoC
    vvv0.vehicle_state = 6;                                     // set vehicle state
    vvv0.moveOneMin();                                                                              
    vvv0.moveOneMin();
    REQUIRE(vvv0.battery_charge > 0);                          // check vehicle/pass distance stats
    REQUIRE(vvv0.flight_distance == 0);
}

TEST_CASE("Vehicle - does vehicle get off charger", "[Vehicle]") {
    Vehicle vvv0(0);                                            // create vehicle
    vvv0.battery_charge = vvv0.battery_capacity*.999;           // leave battery right under full charge
    vvv0.vehicle_state = 6;                                     // charge vehicle
    vvv0.moveOneMin();                                                                              
    vvv0.moveOneMin();
    REQUIRE(vvv0.vehicle_state != 6);                          // make sure it gets off the charger
    REQUIRE(vvv0.battery_charge > vvv0.battery_capacity);
}


// ============== VEHICLE FLEET =====================================

TEST_CASE("VehicleFleet - initialization", "[VehicleFleet]") {
    VehicleFleet vf0(20, 180);                                  // make fleet

    REQUIRE(vf0.vehicles.size() == 20);                         // check size & sim time
    REQUIRE(vf0.maxSimulationTime == 180);
}

TEST_CASE("VehicleFleet - vehicles moving?", "[VehicleFleet]") {
    VehicleFleet vf0(4, 180);                                  // make a fleet and start moving
    vf0.moveOneMin();
    vf0.moveOneMin();                                           // check some stats
    REQUIRE(vf0.vehicles[1].vehicle_state > 1);                 //   on a vehicle to make sure they are doing their thing
    REQUIRE(vf0.presentSimulationTime > 1);                     //   on a fleet variable, to make sure fleet tracking is happening too
}

TEST_CASE("VehicleFleet - check if empty vehicles will queue + charge", "[VehicleFleet]") {
    VehicleFleet vf0(20, 180);                                  // make a fleet of 20
    for (int i = 0 ; i < vf0.vehicles.size() ; ++i){            // kill fleet batteries
        vf0.vehicles[i].battery_charge = 0;                     // make vehicles wait for charger
        vf0.vehicles[i].vehicle_state = 5;
    }

    vf0.moveOneMin();                                           // let the queue sort itself
    vf0.moveOneMin();                   
    vf0.moveOneMin();
    vf0.moveOneMin();                       
                                                                
    REQUIRE(vf0.needing_charging.size() == 17);                 // 3 should be on the charger
    REQUIRE(vf0.chargers.size() == 3);                          // and 17 should be waiting
}

