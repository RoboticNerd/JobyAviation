#include "classes.h"
#include <cstdlib> 

// ============== PASSENGER GROUP =====================================

void PassengerGroup::createPassengers(int numberOfPassengers, int distance) {
    passengers.resize((rand()%(numberOfPassengers) + 1));       // randomize passenger count but at least 1
    destination_distance = rand()%(distance) + 1;               // randomize distance but at least 1km
}

int PassengerGroup::size() {
	return passengers.size();
}

// ============== VEHICLE =============================================
// you create a vehicle by passing the type you want as an int.
Vehicle::Vehicle(int vehicle_type) {
    if (vehicle_type == 0) {
        company = "alpha";                      // name
        cruise_speed = 193.12;                  // kph
        battery_capacity = 320;                 // kWh
        time_to_charge = 36;                    // min
        energy_consumed_cruise = 0.994;         // kWh/km
        max_passengers = 4;                     // count
        fault_probability = 0.0000416667;       // per min

        battery_charge = battery_capacity;      // vehicle starts full

    } else if (vehicle_type == 1) {
        company = "bravo";                      // name
        cruise_speed = 160.93;                  // kph
        battery_capacity = 100;                 // kWh
        time_to_charge = 12;                    // min
        energy_consumed_cruise = 0.932;         // kWh/km
        max_passengers = 5;                     // count
        fault_probability = 0.0000166667;       // per min

        battery_charge = battery_capacity;      // vehicle starts full

    } else if (vehicle_type == 2) {
        company = "charlie";                    // name
        cruise_speed = 257.49;                  // kph
        battery_capacity = 220;                 // kWh
        time_to_charge = 48;                    // min
        energy_consumed_cruise = 1.367;         // kWh/km
        max_passengers = 3;                     // count
        fault_probability = 0.0000083333;       // per min

        battery_charge = battery_capacity;      // vehicle starts full

    } else if (vehicle_type == 3) {
        company = "delta";                      // name
        cruise_speed = 144.84;                  // kph
        battery_capacity = 120;                 // kWh
        time_to_charge = 37.2;                  // min
        energy_consumed_cruise = 0.497;         // kWh/km
        max_passengers = 2;                     // count
        fault_probability = 0.0000366667;       // per min

        battery_charge = battery_capacity;      // vehicle starts full

    } else if (vehicle_type == 4) {
        company = "echo";                       // name
        cruise_speed = 48.28;                   // kph
        battery_capacity = 150;                 // kWh
        time_to_charge = 18;                    // min
        energy_consumed_cruise = 3.604;         // kWh/km
        max_passengers = 2;                     // count
        fault_probability = 0.0001016667;       // per min

        battery_charge = battery_capacity;      // vehicle starts full
    }
}

void Vehicle::loadPassengers(PassengerGroup pass) {
    vehicle_passengers = pass;
    flights++;
}

void Vehicle::unloadPassengers() {
    vehicle_passengers.passengers.clear();
}

void Vehicle::print(){
    std::cout << " " << std::endl;
    std::cout << "Vehicle State =====:            " << vehicle_state << std::endl;
    std::cout << "Faults:                         " << faults << std::endl;
    std::cout << "Flight time:                    " << flight_time << std::endl;
    std::cout << "Flight distance:                " << flight_distance << std::endl;
    std::cout << "Battery charge:                 " << battery_charge << std::endl;
    std::cout << "Distance to airport:            " << distance_to_airport << std::endl;
    std::cout << "Passenger Km:                   " << passengerKm << std::endl;
    std::cout << "Charging time:                  " << charging_time << std::endl;
    std::cout << "Passengers Count =====:         " << vehicle_passengers.size() << std::endl;
    std::cout << "Passenger destination distance: " << vehicle_passengers.destination_distance << std::endl;
    
}

void Vehicle::moveOneMin() {
    // if vehicle is empty but has charge -------------------------------------------
    if (vehicle_state == 1) {
        if (faults > 3){                                            // check if we're faulted out
            vehicle_state = 10;         
        } else {                                                    // otherwise, load the next passengers
            PassengerGroup pass;
            pass.createPassengers(max_passengers, 32);
            loadPassengers(pass);
            distance_to_airport = (int)pass.destination_distance;
        }
        
        vehicle_state = 2;



    // if vehicle is en route to b -------------------------------------------
    } else if (vehicle_state == 2) {
	    //== check if passengers arrived ==//
        if (vehicle_passengers.destination_distance <= 0){          
            unloadPassengers();                                     // if so, get more passengers         
            vehicle_state = 3;     
            
        } else {
        //== otherwise, we're going to ~!FLY!~ ==//
            double distance_covered = cruise_speed/60;
            
            //update PassengerGroup to reduce remaining distance
            vehicle_passengers.destination_distance = vehicle_passengers.destination_distance - distance_covered;

            // update vehicle flight time, distance, battery charge, and faults
            flight_time++;
            flight_distance = flight_distance + distance_covered;
            battery_charge = battery_charge - energy_consumed_cruise*cruise_speed/60;
            passengerKm = passengerKm + vehicle_passengers.size()*distance_covered;
            
            double threshold = 1/fault_probability;                 // first we normalize
            if (rand()%(int)threshold < 2){                         // then we check if a failure proc'd
                faults++;                                           // if it did, increase fault count.

            }
        }



    // if waiting for return passenger -------------------------------------------
    } else if (vehicle_state == 3) {
	    PassengerGroup pass;
        pass.createPassengers(max_passengers, distance_to_airport);
        loadPassengers(pass);
                
        vehicle_state = 4;
      


    // if vehicle is flying to airport -------------------------------------------
    } else if (vehicle_state == 4) {
	    //== check if passengers arrived ==//
        if (vehicle_passengers.destination_distance <= 0){          
            unloadPassengers();
            
            if (battery_charge <= energy_consumed_cruise * 32) {    // check if battery has enough juice for a round trip
                battery_capacity = 0;                               // if not, set battery to zero
                vehicle_state = 5;                                  // and wait for charger
            } else {
                vehicle_state = 1;                                  // if so, get more passengers
            }
            
        } else {
        //== otherwise, we're going to ~!FLY!~ ==//
            double distance_covered = cruise_speed/60;
            
            //update PassengerGroup to reduce remaining distance
            vehicle_passengers.destination_distance = vehicle_passengers.destination_distance - distance_covered;

            // update vehicle flight time, distance, battery charge, and faults
            flight_time++;
            flight_distance = flight_distance + distance_covered;
            battery_charge = battery_charge - energy_consumed_cruise*cruise_speed/60;
            passengerKm = passengerKm + vehicle_passengers.size()*distance_covered;

            double threshold = 1/fault_probability;                 // first we normalize
            if (rand()%(int)threshold < 2){                         // then we check if a failure proc'd
                faults++;                                           // if it did, increase fault count.

            }

        }


    // if vehicle is charging -------------------------------------------
    } else if (vehicle_state == 6) {
        if (battery_charge >= battery_capacity){
            vehicle_state = 1;
            charges++;
        } else {
            battery_charge = battery_charge + battery_capacity/time_to_charge;
            charging_time++;
        }
        
    // if vehicle has faulted out -------------------------------------------
    } else if (vehicle_state == 10) {
        vehicle_state = 10;
    }
}




