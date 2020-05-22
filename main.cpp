/*
* Author: Grant Meehan
* Date: 6/1/19
*
* This file, main.cpp, generates preliminary ArriveEvent objects in the simulation.
* Those ArriveEvent objects then spawn new events when the simulation object is ran.
* The combination of all these events produce an output similar to what is demonstrated below.
*
* Sample Output:
* SOFTWARE GURUS BAR SIMULATION
*
* Time: 4
*  Group of 3 customers arrives
*  Group is seated
* Time: 8
*  Group of 2 customers arrives
*  Group is seated
* Time: 8
*  Serviced order for imported beer
*  Serviced order for local beer
*  Serviced order for local beer
* Time: 9
*  Group of 3 customers leaves
*
* [cont.]
*/

#include "SoftwareGurusBar.h"
#include "Event.h"

#include <iostream>
using namespace std;

int main()
{
  cout << "SOFTWARE GURUS BAR SIMULATION" << endl << endl;

  srand(time(NULL)); //srand(44) is temp const num for testing, use srand(time(NULL)) for real random #

  int t = 0;

  while(t < 240) //240 minutes is max time for possible arrive events
  {
    t += randBetween(2,6); //adds 2-5 minutes between every arrive time
    ArriveEvent *newE = new ArriveEvent(t,randBetween(1,6)); //generates arrive event with group size of 1-5
    theSimulation.scheduleEvent(newE); //adds event to SimulationFramework object PQ
  }

  theSimulation.run(); //cycles through all elements in PQ of SimulationFramework object and updates time

  cout << endl << "Total profits = $" << theBar.getProfit() << endl;

  return 0;
}
