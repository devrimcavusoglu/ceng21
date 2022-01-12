#include "METUMaps.h"
#include "GraphExceptions.h"

#include <iostream>

void METUMaps::PrintNotInJourney() const
{
    std::cout << "Device is not in a journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeDestination() const
{
    std::cout << "Cannot change Destination during journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeStartingLoc() const
{
    std::cout << "Cannot change Starting Location during journey!" << std::endl;
}

void METUMaps::PrintAlreadyInJourney() const
{
    std::cout << "Device is already in a journey!" << std::endl;
}

void METUMaps::PrintJourneyIsAlreadFinished() const
{
    std::cout << "Journey is already finished!" << std::endl;
}

void METUMaps::PrintLocationNotFound() const
{
    std::cout << "One (or both) of the locations are not found in the maps!" << std::endl;
}

void METUMaps::PrintJourneyCompleted() const
{
    std::cout << "Journey Completed!" << std::endl;
}

void METUMaps::PrintCachedLocationFound(const std::string& location0,
                                        const std::string& location1) const
{
    std::cout << "Route between \""
              << location0 << "\" and \""
              << location1 << "\" is in cache, using that..."
              << std::endl;
}

void METUMaps::PrintCalculatingRoutes(const std::string& location0,
                                      const std::string& location1) const
{
    std::cout << "Calculating Route(s) between \""
              << location0 << "\" and \""
              << location1 << "\"..."
              << std::endl;
}

std::string METUMaps::GenerateKey(const std::string& location0,
                                  const std::string& location1)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    return location0 + "/" + location1;
}

METUMaps::METUMaps(int potentialPathCount,
                   const std::string& mapFilePath) {
    this->map = Graph(mapFilePath);
    this->potentialPathCount = potentialPathCount;
    this->inJourney = false;

    int cacheSize = map.TotalVertexCount() * potentialPathCount;
    this->cachedPaths = KeyedHashTable(cacheSize);
}

void METUMaps::SetDestination(const std::string& name) {
    if (this->inJourney) {
        this->PrintUnableToChangeDestination();
        return;
    }
    this->destination = name;
}

void METUMaps::SetStartingLocation(const std::string& name) {
    if (this->inJourney) {
        this->PrintUnableToChangeStartingLoc();
        return;
    }
    this->startingLoc = name;
}

void METUMaps::StartJourney() {
    if (this->inJourney) {
        this->PrintAlreadyInJourney();
        return;
    }

    int start_id = this->LocationId(this->startingLoc);
    int target_id = this->LocationId(this->destination);

    if (start_id == -1 or target_id == -1) {
        this->PrintLocationNotFound();
        return;
    }

    this->PrintCalculatingRoutes(this->startingLoc, this->destination);
    // Compute n = potentialPathCount shortest paths.
    std::vector<std::vector<int> > shortest_paths;
    map.MultipleShortPaths(
        shortest_paths, 
        this->startingLoc, 
        this->destination, 
        this->potentialPathCount
    );


    // Cache the results.
    for (int i = 0; i < shortest_paths.size(); ++i) {
        std::vector<int> current_shortest_path = shortest_paths[i];
        int sub_dest_loc = current_shortest_path[current_shortest_path.size()-1];
        for (int j = 0; j < current_shortest_path.size()-1; j++) {
            int sub_start_loc = current_shortest_path[j]; 
            std::string sub_start_name = map.VertexName(sub_start_loc);
            std::string sub_dest_name = map.VertexName(sub_dest_loc);
            std::string sub_path_key = this->GenerateKey(sub_start_name, sub_dest_name);
            std::vector<int> current_sub_path;

            for (int k = j; k < current_shortest_path.size(); k++)
                current_sub_path.push_back(current_shortest_path[k]);
            cachedPaths.Insert(sub_path_key, current_sub_path);
        }
    }

    this->currentLoc = this->startingLoc;
    this->inJourney = true;
    this->currentRoute = shortest_paths[0];
}

void METUMaps::EndJourney() {
    if (!this->inJourney) {
        this->PrintJourneyIsAlreadFinished();
        return;
    }
    cachedPaths.ClearTable();
    this->startingLoc = "";
    this->destination = "";
    this->currentLoc = "";
    this->inJourney = false;
}

void METUMaps::UpdateLocation(const std::string& name) {
    if (!this->inJourney) {
        this->PrintNotInJourney();
        return;
    }
    else if (name == this->destination) {
        this->PrintJourneyCompleted();
        return;
    }

    int start_id = this->LocationId(this->startingLoc);
    int target_id = this->LocationId(this->destination);

    if (start_id == -1 or target_id == -1) {
        this->PrintLocationNotFound();
        return;
    }

    std::string path_name = this->GenerateKey(name, this->destination);
    std::vector<int> cached_path;
    bool found = this->cachedPaths.Find(cached_path, path_name);
    if (found) {
        this->PrintCachedLocationFound(name, this->destination);
        this->currentRoute = cached_path;
    }
    else {
        this->PrintCalculatingRoutes(name, this->destination);
        std::vector<std::vector<int> > shortest_paths;
        map.MultipleShortPaths(
            shortest_paths, 
            name, 
            this->destination, 
            this->potentialPathCount
        );

        // Cache the results.
        for (int i = 0; i < shortest_paths.size(); ++i) {
        std::vector<int> current_shortest_path = shortest_paths[i];
        int sub_dest_loc = current_shortest_path[current_shortest_path.size()-1];
        for (int j = 0; j < current_shortest_path.size()-1; j++) {
            int sub_start_loc = current_shortest_path[j]; 
            std::string sub_start_name = map.VertexName(sub_start_loc);
            std::string sub_dest_name = map.VertexName(sub_dest_loc);
            std::string sub_path_key = this->GenerateKey(sub_start_name, sub_dest_name);
            std::vector<int> current_sub_path;
            for (int k = j; k < current_shortest_path.size(); k++)
                current_sub_path.push_back(current_shortest_path[k]);
            cachedPaths.Insert(sub_path_key, current_sub_path);
            }
        }
        this->currentRoute = shortest_paths[0];
    }
    this->currentLoc = name;
}

void METUMaps::Display() {
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    if(!inJourney)
    {
        // We are not in journey, this function
        // shouldn't be called
        PrintNotInJourney();
        return;
    }

    int timeLeft = map.TotalWeightInBetween(currentRoute);

    // Print last known location
    std::cout << "Journey         : " << startingLoc << "->"
              << destination << "\n";
    std::cout << "Current Location: " << currentLoc << "\n";
    std::cout << "Time Left       : " << timeLeft << " minutes\n";
    std::cout << "Current Route   : ";
    map.PrintPath(currentRoute, true);

    std::cout.flush();
}


int METUMaps::LocationId(const std::string &name) {
    for (int i = 0; i < this->map.TotalVertexCount(); i++) {
        std::string v_name = map.VertexName(i);
        if (v_name == name)
            return i;
    }
    return -1;
}