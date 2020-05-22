/*
* Author: Grant Meehan
* Date: 6/1/19
*
* This file, Event.h, includes the class definitions for MinPQ, Event, SimulationFramework, and EventComparison.
* Event.h also includes the implementations for Event, SimulationFramework, and EventComparison.
* MinPQ is a class which allows you to create a templated minimum priority queue.
* Event is the parent class of all of the derived Event classes which is used to keep track of what should happen next in priority queue.
* SimulationFramework is a framework which holds the current time in the simulation and the priority queue of events.
* Event comparison is a class which is used to compare 2 event objects, needed for the priority queue.
*/

#ifndef EVENT_H
#define EVENT_H

template <class T>
class MinPQ
{
public:
  // CONSTRUCTORS
  MinPQ();
  MinPQ(int capacity);
  // MEMBER FUNCTIONS
  bool isEmpty();
  void insert(T key);
  T min();
  void delMin();
private:
  // MEMBER VARIABLES
  T *pq;
  int N;
  // MEMBER FUNCTIONS
  void swim(int k);
  void sink(int k, int N);
  bool greater(int i, int j);
  void exch(int i, int j);

};

class Event
{
public:
  Event() : time(-1) {};
  Event(int t) : time(t) {};
  virtual void processEvent(){};
  int getTime() {return time;}

private:
  int time;
};

class SimulationFramework
{
public:
  SimulationFramework() //constructs new SimulationFramework object - default time=0, default size of PQ = 200
  {
    currentTime = 0;
    eventQueue = MinPQ<Event*>(200);
  }
  void scheduleEvent(Event *newEvent) //inserts newly created event into PQ of SimulationFramework
  {
    eventQueue.insert(newEvent);
  }
  void run() //cycles through all elements in PQ of SimulationFramework object and updates time
  {
    while(!eventQueue.isEmpty())
    {
      Event *nextEvent = eventQueue.min();
      eventQueue.delMin();

      currentTime = nextEvent->getTime();

      nextEvent->processEvent();

      delete nextEvent;
    }
  }
  int getCurrentTime() { return currentTime; }
private:
  int currentTime;
  MinPQ<Event*> eventQueue;

};

class EventComparison { //used to compare 2 event objects, needed for the priority queue implementation
  public:
    bool compareEvents(Event *left, Event *right)
    {
      return left->getTime() > right->getTime();
    }
};

#include "MinPQ.cpp"

#endif //EVENT_H
