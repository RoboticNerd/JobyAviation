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




