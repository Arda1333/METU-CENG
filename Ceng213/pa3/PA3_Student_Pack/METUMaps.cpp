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
                   const std::string& mapFilePath)
{
	Graph graph(mapFilePath);
	this -> map = graph;
	KeyedHashTable paths(this -> map.TotalVertexCount() * potentialPathCount);
	this -> cachedPaths = paths;
    this -> potentialPathCount = potentialPathCount;
    this -> inJourney = false;

}

void METUMaps::SetDestination(const std::string& name)
{
    if(inJourney) PrintUnableToChangeDestination();

    else destination = name;
}

void METUMaps::SetStartingLocation(const std::string& name)
{
    if(inJourney) PrintUnableToChangeStartingLoc();

    else startingLoc = name;
}

void METUMaps::StartJourney()
{
	std::vector<std::vector<int> > allPaths;
	std::vector<int> temp;
	int i, j, k, size;
	bool foundStart = false, foundDest = false;

	PrintCalculatingRoutes(startingLoc, destination);
	
	if(inJourney)
	{
		PrintAlreadyInJourney();
		return;
	}

	for(i = 0; i < map.TotalVertexCount(); i++)
	{
		if(map.VertexName(i) == startingLoc) foundStart = true;

		if(map.VertexName(i) == destination) foundDest = true;
	}

	if(!foundStart || !foundDest)
	{
		PrintLocationNotFound();
		return;
	}

    map.MultipleShortPaths(allPaths, startingLoc, destination, potentialPathCount);

    for(i = 0; i < allPaths.size(); i++)
    {
    	size = allPaths[i].size();

    	for(j = 0; j < size - 1; j++)
    	{
    		std::vector<int> tempPath;
    		std::string key = GenerateKey(map.VertexName(allPaths[i][j]), destination);

    		for(k = j; k < size; k++) tempPath.push_back(allPaths[i][k]);

    		cachedPaths.Insert(key, tempPath);
    	}
    }

    currentLoc = startingLoc;
    currentRoute = allPaths[0];
    inJourney = true;
}

void METUMaps::EndJourney()
{
    if(!inJourney)
    {
    	PrintJourneyIsAlreadFinished();
    	return;
    }

    cachedPaths.ClearTable();
    startingLoc = "";
    destination = "";
    currentLoc = "";
    inJourney = false;
}

void METUMaps::UpdateLocation(const std::string& name)
{
	if(!inJourney)
    {
    	PrintNotInJourney();
    	return;
    }


	int vertexCount = map.TotalVertexCount(), i;
	bool locationFound = false, pathFound = false;
	std::vector<int> path;
	std::string key;


    if(destination == name)
    {
    	PrintJourneyCompleted();
    	return;
    }

    for(i = 0; i < vertexCount; i++)
    {
    	if(map.VertexName(i) == name)
    	{
    		locationFound = true;
    		break;
    	}
    }

    if(!locationFound)
    {
    	PrintLocationNotFound();
    	return;
    }

    key = GenerateKey(name, destination);
    pathFound = cachedPaths.Find(path, key);
    currentLoc = name;

    if(pathFound)
    {
    	PrintCachedLocationFound(name, destination);
    	currentRoute = path;
    	return;
    }

    else
    {
    	std::vector<std::vector<int> > allPaths;
    	int j, k, size;

    	PrintCalculatingRoutes(name, destination);
    	map.MultipleShortPaths(allPaths, name, destination, potentialPathCount);
    	currentRoute = allPaths[0];

    	for(i = 0; i < allPaths.size(); i++)
    	{
    		size = allPaths[i].size();

    		for(j = 0; j < size - 1; j++)
    		{
    			std::vector<int> tempPath;
    			key = GenerateKey(map.VertexName(allPaths[i][j]), destination);

    			for(k = j; k < size; k++) tempPath.push_back(allPaths[i][k]);

    			cachedPaths.Insert(key, tempPath);
    		}
    	}
    }

}

void METUMaps::Display()
{
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