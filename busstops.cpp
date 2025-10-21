/*busstops.cpp*/

//
// A collection of bus stops in the Open Street Map.
// 
// Rachel Li
// Northwestern University
// CS 211
// 

#include <iostream>
#include <string>
#include "busstops.h"
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <utility>
#include "dist.h"
#include <map>

using namespace std;

  //
  // readMapBusStops
  //
  // Given an text file name, reads through the document and 
  // stores all the bus stops into the given vector.
  //
  void BusStops::readMapBusStops(string busdoc)
{  ifstream input;
   input.open(busdoc);

   string line;
   getline(input, line);

   while(!line.empty())
   {
    stringstream parser(line); // setup to parse the line
    string stopid, busroute, stopname, direction, location, lat, lon;

    getline(parser, stopid, ',');
    getline(parser, busroute, ',');
    getline(parser, stopname, ',');
    getline(parser, direction, ',');
    getline(parser, location, ',');
    getline(parser, lat, ',');
    getline(parser, lon, ',');

    struct BusStop BS(stoi(stopid), stoi(busroute), stopname, direction, location, stod(lat), stod(lon));

    this->MapBusStops.push_back(BS);
    getline(input, line);
   }

}

  //
  // print
  //
  // prints each bus stop to the console.
  //
  void BusStops::print()
  {
    for (BusStop& BS : this->MapBusStops) {
    BS.print();
  }
  }

//
// accessors / getters
//
  int BusStops::getNumMapBusStops()
  {
    return (int) this->MapBusStops.size();
  }


// gets closest stop in a given direction from a building
  pair<double, BusStop> BusStops::closestStop(double bLat, double bLon, string direction)
  {
    double dist;
    map<double, BusStop> collection;

    for (const BusStop& BS : this->MapBusStops)
    {
      if (BS.dir == direction)
      {
        dist = distBetween2Points(bLat, bLon, BS.lat, BS.lon);

        collection.emplace(dist, BS);
      }
    }
    return make_pair(collection.begin()->first, collection.begin()->second);


  }