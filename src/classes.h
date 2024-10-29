#include <iostream>
#include <vector>
#include <string>

// This is a structure that helps organize the final results.
struct SummaryStruc {
    int flights = 0;
    int flight_time = 0;
    double flight_distance = 0;
    int charges = 1;
    int time_charging = 0;
    int faults = 0;
    double passengerKm = 0;
};



// This is a structure that defines a passenger.
struct Passenger {
    // why even have this? What if we need to keep track of tall passengers
    //    who are willing to pay for for more leg-room? Or what about kids
    //    who require a baby seat? Is that a thing for small aircraft?
    public:
    private:
};


// Class for managing groups of passengers. The number one use is to track the
//    destination distance of the passengers.
class PassengerGroup {
	public:
        void createPassengers(int numberOfPassengers, int flight_distance);

		int size();

        // tracked assets
        int destination_distance;               // km

		std::vector<Passenger> passengers; 
};


// Class for managing a vehicle and tracking its stats. It holds "PassengerGroups"
//    and stores vehicle stats throughout the simulation.
class Vehicle {
    public:
        Vehicle(int vehicle_type);
        void moveOneMin();

        void loadPassengers(PassengerGroup pass);
        void unloadPassengers();
        void print();

        int vehicle_state = 1;                  // 1) waiting for passengers
                                                // 2) flying to b 
                                                // 3) waiting for return passengers
                                                // 4) flying to airport
                                                // 5) waiting for charger
                                                // 6) charging
                                                // 10) faulted out

        // tracked assets
        int faults = 0;                         // count
        int flight_time = 0;                    // min
        double flight_distance = 0;             // km
        double battery_charge;                  // kWh
        int distance_to_airport = 0;            // km
        double passengerKm = 0;                 // passenger km
        PassengerGroup vehicle_passengers;      // passenger group
        int charging_time = 0;                  // min

        int charges = 0;
        int flights = 0;                        // #

        // static vehicle preloads
        std::string company;                    // name
        double cruise_speed;                    // kph
        double battery_capacity;                // kWh
        double time_to_charge;                  // min
        double energy_consumed_cruise;          // kWh/km
        int max_passengers;                     // count
        double fault_probability;               // per min

};


// Manages the entire fleet. Also coordinates charging amongst the vehicles.
//    This is called for every step during the simulation (current step
//    size, 1 min).
class VehicleFleet {
    public:
        VehicleFleet(int vehicles_count, int sim_time);
        
        void moveOneMin();
        void handleCharging();
        void print();
        void finalPrint();

        std::vector<Vehicle> vehicles;

        int presentSimulationTime = 0;
        int maxSimulationTime = 0;

        std::vector<int> chargers;
        std::vector<int> needing_charging;

};
