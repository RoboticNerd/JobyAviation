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


