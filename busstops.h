/*busstops.h*/

//
// A collection of bus stops in the Open Street Map.
// 
// Rachel Li
// Northwestern University
// CS 211
// 

#pragma once

#include <iostream>
#include <string>
#include "busstop.h"
#include <vector>


using namespace std;

//
// Keeps track of all the bus stops in the map.
//
class BusStops
{
public:
  vector<BusStop> MapBusStops;

  //
  // readMapBusStops
  //
  // Given an text file name, reads through the document and 
  // stores all the bus stops into the given vector.
  //
  void readMapBusStops(string busdoc);

  //
  // print
  //
  // prints each bus stop to the console.
  //
  void print();

  //
  // accessors / getters
  //
  int getNumMapBusStops();

  pair<double, BusStop> closestStop(double bLat, double bLon, string direction);
};