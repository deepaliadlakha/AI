/*************************

Event class describes a simulation "event". A simulation "event" is
defined by an ID, a type and a time at which the event is scheduled.

**********************/

#ifndef EVENT_H                           // avoid repeated expansion
#define EVENT_H
#include <iostream>
using namespace std;

class Event {

 private:
  int ID;
  int type; 
  double time;
 // long a[10000];

 
  
 public:
  Event() {ID=2; type=3; time=4;}  //default constructor
					   //creates an arrival event
					   //at time 0
  Event(int id, int ty, double ti);  
  bool operator<(const Event& e) const;   //overload "<" to compare events
  bool operator==(const Event& e) const;
  bool operator!=(const Event& e) const;
  void print(ostream & outstream=cout) const; //forgot why I needed this
  double getTime() const;                   //accessor method
  int getType() const;                      //accessor method
};


#endif
