#include <iostream>
#include "classes.h"

int main () {
    int simulation_time = 180;                                      // simulation runtime
    int vehicle_count = 20;                                         // # of vehicles in fleet

    VehicleFleet fleet( 20, 180);                                   // create fleet

                                                    
    while(fleet.presentSimulationTime < fleet.maxSimulationTime){   // itterate until complete
        fleet.moveOneMin();
    }

    fleet.finalPrint();                                             // show the results

    return 0;
}