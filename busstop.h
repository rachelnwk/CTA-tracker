/*busstop.h*/

//
// A bus stop in the Open Street Map.
// 
// Rachel Li
// Northwestern University
// CS 211
// 

#pragma once
#include <iostream>
#include <string>
#include "curl_util.h"


using namespace std;

//
// BusStop
//
// Defines a bus stop with its stop ID, bus route, stop name,
// direction of travel, location of stop, and position
//
class BusStop
{
public:
  int stopID;
  int busRoute;
  string stopName;
  string dir;
  string location;
  double lat;
  double lon;


  //
  // constructor
  //
  BusStop(int stopid, int busroute, string stopname, string dirr, string locationn, double latt, double lonn);

  //
  // print
  //
  // prints each bus stop to the console.
  //
  void print();

  void printBusPredictions(CURL* curl, string url);

};