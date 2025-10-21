/*building.cpp*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#include <iostream>
#include <iomanip>

#include "nodes.h"
#include "node.h"
#include "building.h"
#include "dist.h"
#include "busstop.h"
#include "busstops.h"

using namespace std;


//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  //this->ID = id;
  //this->Name = name;
  //this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// print
// 
// prints information about a building --- id, name, etc. -- to
// the console. The function is passed the Nodes for searching 
// purposes.
//
void Building::print(Nodes& nodes)
{
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;
  cout << "# perimeter nodes: " << this->NodeIDs.size() << endl;
  // new code
  cout << "Location: (" << this->getLocation(nodes).first << ", ";
  cout << this->getLocation(nodes).second << ")" << endl;

  cout << endl;

/*
  cout << "Nodes:" << endl;
  for (long long nodeid : this->NodeIDs)
  {
    cout << "  " << nodeid << ": ";

    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeid, lat, lon, entrance);

    if (found) {
      cout << "(" << lat << ", " << lon << ")";

      if (entrance)
        cout << ", is entrance";

      cout << endl;
    }
    else {
      cout << "**NOT FOUND**" << endl;
    }
  }//for
  */
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}

//
// gets the center (lat, lon) of the building based
// on the nodes that form the perimeter
//
pair<double, double> Building::getLocation(const Nodes& nodes)
{
  double avgLat = 0;
  double avgLon = 0;
  double lat = 0;
  double lon = 0;
  bool entrance = false;
  
  int count = (int) this->NodeIDs.size();
  for (long long nodeid : this->NodeIDs)
  {
  bool found = nodes.find(nodeid, lat, lon, entrance);

  if (found)
  {
    avgLat = (double) avgLat + lat;
    avgLon = (double) avgLon + lon;
  }
  else // didnt find it, take off of count
  {
    count = count - 1;
  }
  }

  avgLat = (double) avgLat / count;
  avgLon = (double) avgLon / count;

  
  return make_pair(avgLat, avgLon);
}

