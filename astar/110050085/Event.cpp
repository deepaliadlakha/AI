#include "Event.h"
#include "declarations.h"
using namespace std;

Event::Event(int id=0, int ty=0, double ti=0.0) {
  ID=id; type=ty; time=ti;
}

//Overload "less than" operator
//Why is this doing the opposite of what it should? Forgot!!
//This is what happens when you don't comment code, I swear I did this myself!
bool Event::operator<(const Event& e) const  {
  return (time > e.time);
}
bool Event::operator==(const Event& e) const  {
  
  return ((ID == e.ID) && (type == e.type) && (time == e.time) );
}

bool Event::operator!=(const Event& e) const  {
  
  return (!((ID == e.ID) && (type == e.type) && (time == e.time)) );
}


void Event::print(ostream & outstream) const {
  outstream << "ID: " << ID << ", type=" << type << ", time=" << time << endl;
}
  
double Event::getTime() const { return time;}
int Event::getType() const {return type;}

