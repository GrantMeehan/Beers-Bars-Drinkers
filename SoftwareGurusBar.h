/*
* Author: Grant Meehan
* Date: 6/1/19
*
* This file, SoftwareGurusBar.h, includes the class definitions and implementations for randomInteger, SoftwareGurusBar, ArriveEvent, OrderEvent, LeaveEvent, and ReorderEvent
* randomInteger is a helper class which is used to easily create an integer in a desired range
* SoftwareGurusBar keeps track of the number of free chairs in the bar and the profit of the bar.
* ArriveEvent is a derived class of the Event class. An object of this class is created and processed every time a new customer arrives. When processed, it creates an order event.
* OrderEvent is a derived class of the Event class. An object of this class is created and processed after arrival or reorder. When processed, it creates either a reorder or leave event.
* LeaveEvent is a derived class of the Event class. An object of this class is created and processed after a group orders but decides not to reorder.
* ReorderEvent is a derived class of the Event class. An object of this class is created and processed after a group orders and decides to reorder. When processed, it creates a reorder event.
*/

#ifndef SOFTWAREGURUSBAR_H
#define SOFTWAREGURUSBAR_H

#include "Event.h"
#include <iostream>
using namespace std;

SimulationFramework theSimulation;

class randomInteger {
  public:
    unsigned int operator()(unsigned int);
} randomizer;

unsigned int randomInteger::operator()(unsigned int max) //overloaded operator, helper for randBetween(int, int)
{
  unsigned int rval = rand();
  return rval % max;
}
unsigned int randBetween(int low, int high) { //generates random number between 2 integers
  return low + randomizer(high - low);
}

class SoftwareGurusBar
{
public:
  // CONSTRUCTORS
  SoftwareGurusBar() : freeChairs(50) {}
  SoftwareGurusBar(int fc) : freeChairs(fc) {}
  // MEMBER FUNCTIONS
  int getProfit() {return profit;}
  bool canSeat(int partySize) //informs user of group arrival, determines if party of given size will fit in bar provided number of seats left in bar. Sits party if enough seats, turns away party if not enough seats
  {
    cout << "Time: " << theSimulation.getCurrentTime() << endl;
    cout << " Group of " << partySize << " customers arrives" << endl;
    if (partySize < freeChairs) {
      cout << " Group is seated" << endl;
      freeChairs -= partySize;
      return true;
    }
    else {
      cout << " No room, group leaves" << endl;
      return false;
    }
  }
  void order(int groupSize) //informs user orders for each member of party using randomly selected beer choices and increases depending on beer type ordered
  {
    //serve beer
    cout << "Time: " << theSimulation.getCurrentTime() << endl;
    for (int i = 0; i < groupSize; i++) {
      int beerType = randBetween(1,4);
      if (beerType == 1) {
        cout << " Serviced order for local beer" << endl;
        profit += 2;
      }
      else if (beerType == 2) {
        cout << " Serviced order for imported beer" << endl;
        profit += 3;
      }
      else if (beerType == 3) {
        cout << " Serviced order for special beer" << endl;
        profit += 4;
      }
    }
  }
  void leave(int partySize) //informs user that party has left and increases free chairs in bar
  {
    //leave, free chairs
    cout << "Time: " << theSimulation.getCurrentTime() << endl;
    cout << " Group of " << partySize << " customers leaves" << endl;
    freeChairs += partySize;
  }

private:
  // MEMBER VARIABLES
  int freeChairs;
  double profit;
};

SoftwareGurusBar theBar;

class ArriveEvent : public Event
{
public:
  ArriveEvent() : Event(), groupSize(0) {}
  ArriveEvent(int t, int gSize) : Event(t), groupSize(gSize) {}
  virtual void processEvent();
private:
  int groupSize;
};

class OrderEvent : public Event
{
public:
  OrderEvent() : Event(), groupSize(0) {}
  OrderEvent(int t, int gSize) : Event(t), groupSize(gSize) {}
  virtual void processEvent();
private:
  int groupSize;
};

class LeaveEvent : public Event
{
public:
  LeaveEvent() : Event(), groupSize(0) {}
  LeaveEvent(int t, int gSize) : Event(t), groupSize(gSize) {}
  virtual void processEvent();
private:
  int groupSize;
};

class ReorderEvent : public Event
{
public:
  ReorderEvent() : Event(), groupSize(0) {}
  ReorderEvent(int t, int gSize) : Event(t), groupSize(gSize) {}
  virtual void processEvent();
private:
  int numReorders;
  int groupSize;
};

void ArriveEvent::processEvent()  //Determines if bar can seat party. If so, generates order event and adds it to PQ with random order time 2-10 minutes
{
  if (theBar.canSeat(groupSize)) {
    OrderEvent *newE = new OrderEvent(theSimulation.getCurrentTime() + randBetween(2,11),groupSize);
    theSimulation.scheduleEvent(newE);
  }
}

void OrderEvent::processEvent() //40% chance LeaveEvent is generated and added to PQ, 60% chance ReorderEvent is generated and added to PQ
{
  theBar.order(groupSize);

  int r = randBetween(1,11);
  if (r < 5) {
    LeaveEvent *newE = new LeaveEvent(theSimulation.getCurrentTime() + 1, groupSize);
    theSimulation.scheduleEvent(newE);
  }
  else
  {
    ReorderEvent *newE = new ReorderEvent(theSimulation.getCurrentTime() + 1, groupSize);
    theSimulation.scheduleEvent(newE);
  }
}

void LeaveEvent::processEvent() //informs user party has left
{
  theBar.leave(groupSize);
}

void ReorderEvent::processEvent() //if party has reordered less than 4 times, generates new order event and adds it to PQ with random order time 2-10 minutes
{
  if (numReorders < 4) {
    numReorders++;
    OrderEvent *newE = new OrderEvent(theSimulation.getCurrentTime() + randBetween(2,11), groupSize);
    theSimulation.scheduleEvent(newE);
  }
  else
  {
    LeaveEvent *newE = new LeaveEvent(theSimulation.getCurrentTime(), groupSize);
    theSimulation.scheduleEvent(newE);
  }



}

#endif //SOFTWAREGURUSBAR_H
