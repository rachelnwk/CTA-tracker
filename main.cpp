/*main.cpp*/

//
// Program to input Nodes (positions) and Buildings from
// an Open Street Map file.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "building.h"
#include "buildings.h"
#include "node.h"
#include "nodes.h"
#include "busstop.h"
#include "busstops.h"
#include "osm.h"
#include "dist.h"
#include "tinyxml2.h"
#include "curl_util.h"

using namespace std;
using namespace tinyxml2;

// sort by id
bool sortbyid(BusStop bs1, BusStop bs2)
{
  return (bs1.stopID < bs2.stopID);
}

//
// main
//
int main()
{
  XMLDocument xmldoc;
  Nodes nodes;
  Buildings buildings;
  BusStops busstops;
  
  cout << "** NU open street map **" << endl;

  string filename;

  cout << endl;
  cout << "Enter map filename> " << endl;
  getline(cin, filename);

  //
  // 1. load XML-based map file 
  //
  if (!osmLoadMapFile(filename, xmldoc))
  {
    // failed, error message already output
    return 0;
  }
  
  //
  // 2. read the nodes, which are the various known positions on the map:
  //
  nodes.readMapNodes(xmldoc);

  //
  // 3. read the university buildings:
  //
  buildings.readMapBuildings(xmldoc);

  //
  // read bus stops
  //
  busstops.readMapBusStops("bus-stops.txt");
  sort(busstops.MapBusStops.begin(), busstops.MapBusStops.end(), sortbyid);

  //
  // initialize CURL library
  //
  CURL* curl = curl_easy_init();
  if (curl == nullptr)
  {
    cout << "**ERROR:" << endl;
    cout << "**ERROR: unable to initialize curl library" << endl;
    cout << "**ERROR:" << endl;
    return 0;
  }

  //
  // 4. stats
  //
  cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
  cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
  cout << "# of bus stops: " << busstops.getNumMapBusStops() << endl;

  //
  // 5. now let the user for search for 1 or more buildings:
  //
  while (true)
  {
    string name;

    cout << endl;
    cout << "Enter building name (partial or complete), or * to list, or @ for bus stops, or $ to end> " << endl;

    getline(cin, name);

    if (name == "$") {
      break;
    }
    else if (name == "*") {
      buildings.print();
    }
    else if (name == "@") {
      busstops.print();
    }
    else {
      buildings.findAndPrint(name, nodes, busstops, curl);
    }

  }//while

  //
  // done:
  //
curl_easy_cleanup(curl);

  cout << endl;
  cout << "** Done **" << endl;

  return 0;
}
