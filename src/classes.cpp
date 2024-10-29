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




// ============== VEHICLE FLEET =====================================

VehicleFleet::VehicleFleet(int vehicles_count, int sim_time) {
    maxSimulationTime = sim_time;                               // store sim time

    for ( int i = 0 ; i < vehicles_count ; i++ ) {              // create and store your vehicles
        Vehicle created(rand()%5);                              // randomly
        vehicles.push_back(created);
    }

}

void VehicleFleet::handleCharging() {
    chargers.clear();

    for ( int i = 0 ; i < vehicles.size() ; i++ ) {             // cycle through all vehicles
        if (vehicles[i].vehicle_state == 6){                    // take note of the ones still charging
            chargers.push_back(i);
        };
        if (vehicles[i].vehicle_state == 5){                    // take note of those that need charging
            needing_charging.push_back(i);
            vehicles[i].vehicle_state = 20;
        }
    }
        
    if (chargers.size() < 3 && needing_charging.size() > 0){    // if there are chargers open
        vehicles[needing_charging[0]].vehicle_state = 6;        // begin a vehicle charging

        std::vector<int> temp;                                      // really? There's no pop front for vectors?
        for (int i = 0; i < (needing_charging.size() - 1) ; i++){   //   alright well, diy pop front here
            temp.push_back(needing_charging[i+1]);
        }
        needing_charging.clear();
        needing_charging = temp;
    }

}



void VehicleFleet::moveOneMin() {                               // And this is where the magic happens

    handleCharging();                                           // handle charging for the fleet if needed
    
    for ( int i = 0 ; i < vehicles.size() ; i++ ) {             // iterate all vehicle simulations
        vehicles[i].moveOneMin();
    }

    presentSimulationTime++;                                    // and tick sim time
}



void VehicleFleet::print() {                                    // just printing fleet stats
    std::cout << " " << std::endl;
    std::cout << "Chargers: [";


    for(int i = 0 ; i < chargers.size(); i++){
        std::cout << " " << chargers[i];
    }
    std::cout << "];" << std::endl;


    std::cout << "Needing Charging: [";
    for(int i = 0 ; i < needing_charging.size(); i++){
        std::cout << " " << needing_charging[i];
    }
    std::cout << "];" << std::endl;


    std::cout << "Vehicle States: [";
    for(int i = 0 ; i < vehicles.size(); i++){
        std::cout << " " << vehicles[i].vehicle_state;
    }
    std::cout << "];" << std::endl;


    std::cout << "Present sim time: " << presentSimulationTime << std::endl;

    std::cout << "Vehicle SoC: [";
    for(int i = 0 ; i < vehicles.size(); i++){
        std::cout << " " << vehicles[i].battery_charge;
    }
    std::cout << "];" << std::endl;


}


void VehicleFleet::finalPrint() {
    // Per vehicle type feels a bit like a wierd request. But maybe it's on purpose?
    // Note: this isn't how I would approach this typically, but it's late... 
    // So, todo: Make this area more sustainable.

    // initialize our structures for summarization
    SummaryStruc alpha;
    SummaryStruc bravo;
    SummaryStruc charlie;
    SummaryStruc delta;
    SummaryStruc echo;
    
    // iterate through the vehicle stats storing all of the relevant data into the summary structures
    for (int i = 0; i < vehicles.size() ; i++ ){
        if (vehicles[i].company == "alpha"){
            alpha.flights = alpha.flights + vehicles[i].flights;
            alpha.flight_time = alpha.flight_time + vehicles[i].flight_time;
            alpha.flight_distance = alpha.flight_distance + vehicles[i].flight_distance;
            alpha.charges = alpha.charges + vehicles[i].charges;
            alpha.time_charging = alpha.time_charging + vehicles[i].charging_time;
            alpha.faults = alpha.faults + vehicles[i].faults;
            alpha.passengerKm = alpha.passengerKm + vehicles[i].passengerKm;

        } else if (vehicles[i].company == "bravo"){
            bravo.flights = bravo.flights + vehicles[i].flights;
            bravo.flight_time = bravo.flight_time + vehicles[i].flight_time;
            bravo.flight_distance = bravo.flight_distance + vehicles[i].flight_distance;
            bravo.charges = bravo.charges + vehicles[i].charges;
            bravo.time_charging = bravo.time_charging + vehicles[i].charging_time;
            bravo.faults = bravo.faults + vehicles[i].faults;
            bravo.passengerKm = bravo.passengerKm + vehicles[i].passengerKm;
        
        } else if (vehicles[i].company == "charlie"){
            charlie.flights = charlie.flights + vehicles[i].flights;
            charlie.flight_time = charlie.flight_time + vehicles[i].flight_time;
            charlie.flight_distance = charlie.flight_distance + vehicles[i].flight_distance;
            charlie.charges = charlie.charges + vehicles[i].charges;
            charlie.time_charging = charlie.time_charging + vehicles[i].charging_time;
            charlie.faults = charlie.faults + vehicles[i].faults;
            charlie.passengerKm = charlie.passengerKm + vehicles[i].passengerKm;

        } else if (vehicles[i].company == "delta"){
            delta.flights = delta.flights + vehicles[i].flights;
            delta.flight_time = delta.flight_time + vehicles[i].flight_time;
            delta.flight_distance = delta.flight_distance + vehicles[i].flight_distance;
            delta.charges = delta.charges + vehicles[i].charges;
            delta.time_charging = delta.time_charging + vehicles[i].charging_time;
            delta.faults = delta.faults + vehicles[i].faults;
            delta.passengerKm = delta.passengerKm + vehicles[i].passengerKm;
        
        } else if (vehicles[i].company == "echo"){
            echo.flights = echo.flights + vehicles[i].flights;
            echo.flight_time = echo.flight_time + vehicles[i].flight_time;
            echo.flight_distance = echo.flight_distance + vehicles[i].flight_distance;
            echo.charges = echo.charges + vehicles[i].charges;
            echo.time_charging = echo.time_charging + vehicles[i].charging_time;
            echo.faults = echo.faults + vehicles[i].faults;
            echo.passengerKm = echo.passengerKm + vehicles[i].passengerKm;

        }
    }

    // Now lets print it all out
    std::cout << "Vehicle Types:                                  [ Alpha   Bravo   Charlie Delta   Echo    ];" << std::endl;
    std::cout << "Average flight time per flight (min):           [ " << alpha.flight_time/alpha.flights << "       " << bravo.flight_time/bravo.flights << "       " << charlie.flight_time/charlie.flights << "       " << delta.flight_time/delta.flights << "       " << echo.flight_time/echo.flights << "      ];" << std::endl; 
    std::cout << "Average distance per flight (km):               [ " << alpha.flight_distance/alpha.flights << " " << bravo.flight_distance/bravo.flights << " " << charlie.flight_distance/charlie.flights << " " << delta.flight_distance/delta.flights << " " << echo.flight_distance/echo.flights << " ];" << std::endl; 
    std::cout << "Average time charging per charge session (min): [ " << alpha.time_charging/alpha.charges << "       " << bravo.time_charging/bravo.charges << "      " << charlie.time_charging/charlie.charges << "      " << delta.time_charging/delta.charges << "       " << echo.time_charging/echo.charges << "       ];" << std::endl; 
    std::cout << "Total faults (count):                           [ " << alpha.faults << "       " << bravo.faults << "       " << charlie.faults << "       " << delta.faults << "       " << echo.faults << "       ];" << std::endl; 
    std::cout << "Total passenger kilometers (km):                [ " << alpha.passengerKm << " " << bravo.passengerKm << " " << charlie.passengerKm << " " << delta.passengerKm << "  " << echo.passengerKm << " ];" << std::endl; 

}