/** Main testing all functions with a different object **/

#include<iostream>
#include "hashIITB.h"
#include "Event.h"

using namespace std;

/****
Overload << operator so that cout works to print Event objects
Needed for trace/debugging
****/

ostream & operator << (ostream& ostr, const Event& e) {
  e.print(ostr);
  return ostr;
}


int main(void){

  Event ev_arr[20];
  HashIITB<Event, int> eventMap;
  int i;

  for (i=0; i < 20; i ++) {
    Event e(i+10, i+11, (i+11)*(i+11));
    //    cout << "Inserting: " << e;
    ev_arr[i]=e;
    eventMap.insert(e, i+15);
    //    cout << "value: " << i+15 << endl;;
    if (i%4 == 0) {
      // cout << e ;
      eventMap.insert(e, i+18);
      eventMap.insert(e, i+10);
      eventMap.insert(e, i+23);
      // cout << "values: " << i+18  << " " << i+10 << " " << i+ 23 << endl;
    }

  }

  cout << "Size of map: " << eventMap.size() << endl;
  for (i=0; i < 20; i ++) {
    Event e(i+10, i+11, (i+11)*(i+11));
    ev_arr[i]=e;
    if (i%8 == 0) {
      // cout << "deleting "<< e ;
      eventMap.deleteFirst(e);
    }
  }

  for (i=0; i < 20; i ++) {
    Event e(i+10, i+11, (i+11)*(i+11));
    ev_arr[i]=e;
    if (i%5 == 0) {
      // cout << "Inserting: " << e;
      // cout << e ;
      // cout << "value: " << i+21 << endl;;
      eventMap.insert(e, i+21);
    }
  }
    
  Event e1(19,20,400); //This key should be there in the map, value
		       //inserted  is 24
  pair<bool,int> findResult = eventMap.findFirst(e1);
  cout << findResult.first << " " << findResult.second << endl;
  Event e2(14,15,225);
  findResult = eventMap.findFirst(e2);
  cout << findResult.first << " " << findResult.second << endl;

  pair<int,list<int> > findResults = eventMap.findAll(e2);
  cout << findResults.first << endl;

  while (!(findResults.second).empty()) {
    cout << (findResults.second).front() << " ";
    (findResults.second).pop_front();
  }
  cout << endl;

  findResult = eventMap.deleteFirst(e2);
  
  findResults = eventMap.findAll(e2);

  cout << findResults.first << endl;
  while (!(findResults.second).empty()) {
    cout << (findResults.second).front() << " ";
    (findResults.second).pop_front();
  }
  cout << endl;

  findResults = eventMap.deleteAll(e2);
  cout << findResults.first << endl;
  while (!(findResults.second).empty()) {
    cout << (findResults.second).front() << " ";
    (findResults.second).pop_front();
  }
  cout << endl;
  findResults = eventMap.findAll(e2);
  cout << findResults.first << endl;
  while (!(findResults.second).empty()) {
    cout << (findResults.second).front() << " ";
    (findResults.second).pop_front();
  }

  eventMap.insert(e2,99);
  eventMap.insert(e2,20);

  findResults = eventMap.findAll(e2);
  cout << findResults.first << endl;
  while (!(findResults.second).empty()) {
    cout << (findResults.second).front() << " ";
    (findResults.second).pop_front();
  }
  cout << endl;
  
}

