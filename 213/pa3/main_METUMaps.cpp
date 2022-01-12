#include "METUMaps.h"
#include <iostream>

int main()
{
    METUMaps maps(2, "metu_campus.map");

    // Set Proper Locations
    maps.SetStartingLocation("A4_Gate");
    maps.SetDestination("A7_Gate");
    maps.StartJourney();
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("C_Statue");
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("Tekno_A8");
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("A7_Gate");
    maps.EndJourney();

    // ======================== //
    // OUTPUT OF THE CODE ABOVE //
    // ======================== //
    // Calculating Route(s) between "Ceng" and "Library"...
    // ================
    // Journey         : Ceng->Library
    // Current Location: Ceng
    // Time Left       : 7 minutes
    // Current Route   : Ceng--5->EE--2->Library
    // ================
    // Route between "EE" and "Library" is in cache, using that...
    // ================
    // Journey         : Ceng->Library
    // Current Location: EE
    // Time Left       : 2 minutes
    // Current Route   : EE--2->Library
    // ================
    // Journey Completed!

}