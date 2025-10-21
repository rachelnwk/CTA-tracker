/*busstop.cpp*/

//
// A bus stop in the Open Street Map.
// 
// Rachel Li
// Northwestern University
// CS 211
// 

#include <iostream>
#include <iomanip>
#include <stdexcept>

#include "busstop.h"
#include "curl_util.h"

#include "json.hpp"
using json = nlohmann::json;


using namespace std;

//
// constructor
//
BusStop::BusStop(int stopid, int busroute, string stopname, string dirr, string locationn, double latt, double lonn)
: stopID(stopid), busRoute(busroute), stopName(stopname), dir(dirr), location(locationn), lat(latt), lon(lonn)
{}

  //
  // print
  //
  // prints each bus stop to the console.
  //
  void BusStop::print()
  {
    cout << this->stopID << ": bus " << this->busRoute <<  ", ";
    cout << this->stopName << ", " << this->dir << ", " << this->location;
    cout << ", location (" << this->lat << ", "  << this->lon << ")" << endl;
  }

void BusStop::printBusPredictions(CURL* curl, string url)
{
  string response;
      bool success = callWebServer(curl, url, response);

      if (!success)
      {
        cout << "  <<bus predictions unavailable, call failed>>" << endl;
      }
      else
      {
        auto jsondata = json::parse(response);
        auto bus_response = jsondata["bustime-response"];
        auto predictions = bus_response["prd"];

        if (predictions.empty())
        cout << "  <<no predictions available>>" << endl;

        // for each predictions (a map) in the list:
        for (auto& M : predictions) {
        try {
          cout << "  vehicle #" << stoi( M["vid"].get_ref<std::string&>() ) << " on route " << stoi( M["rt"].get_ref<std::string&>() );
          cout << " travelling " << M["rtdir"].get_ref<std::string&>() << " to arrive in " << stoi( M["prdctdn"].get_ref<std::string&>() ) << " mins" << endl;
        }
        catch (exception& e)
        {
          cout << "  error" << endl;
          cout << "  malformed CTA response, prediction unavailable" << " (error: " << e.what() << ")" << endl;
        }
        }


      }
}
