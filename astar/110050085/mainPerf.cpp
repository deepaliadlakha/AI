/**
 *
Main file for checking performance characteristics of your hashtable ADT:
-Time required for various operations
-Memory required (two indicators for this: resident size in KBs and Page Faults
Your ADT will be evaluated using these metrics.

For all of these metrics: SMALLER IS BETTER, but there are space-time trade-offs.

**/
#include<iostream>
#include<cstdlib>
#include<sys/time.h>
#include <list>
#include<sys/resource.h>
#include "hashIITB.h"
#include "timeTracker.h"
#include "Event.h"

using namespace std;

int const NUM_TESTS =  3000;// Loop running limit
int const VALUE_LIMIT = 1000;//Upper bound on `key',`value' that can be inserted. 

int main(int argc,char* argv[]){
	if(argc!=2){
		cerr<<"Wrong usage."<<endl;
		cerr<<"Correct usage : ./a.out <any positive integer (for random number generator)>"<<endl;
		exit(1);
	}
	srand(atoi(argv[1])); //seed to random number generator

	HashIITB<Event, int> eventSet; //some arbitrary map to test
				       //the hashtable ADT. Key is
				       //event object, value is int
	


	int value = 0;
	//Variables required for the resource usage code
	int memUsage = -1;
	int numPageFaults = -1;
	struct rusage resourceUsage;
	int isSuccessful = -1;
	//starting timer here
	startTimer();
	//start arbitrary operations
	for(int i = 0; i < NUM_TESTS/4;i++){
	  //generating random  RECORDS 
	  value = rand()%VALUE_LIMIT;
	  Event key(value, value%2, value);
	  //insert the record
	  eventSet.insert(key, value);
	}
	//memory usage snapshot
	isSuccessful = getrusage(RUSAGE_SELF,&resourceUsage);//get resource usage statistics of process till now.
	if(isSuccessful == 0){
	  cout << "RSS: "<< (memUsage = resourceUsage.ru_maxrss) << "  PF: "
	       << (numPageFaults = resourceUsage.ru_majflt) << endl; 
	}
	else{
		cerr<<"getrusage() failed"<<endl;
	}

	for(int i = 0; i < NUM_TESTS/4;i++){
	  //generating random  RECORDS 
	  value = rand()%VALUE_LIMIT;
	  Event key(value, value%2, value);
	  //insert the record
	  eventSet.insert(key, value);
	}
	//memory usage snapshot
	isSuccessful = getrusage(RUSAGE_SELF,&resourceUsage);//get resource usage statistics of process till now.
	if(isSuccessful == 0){
	  cout << "RSS: "<< (memUsage = resourceUsage.ru_maxrss) << "  PF: "
	       << (numPageFaults = resourceUsage.ru_majflt) << endl; 
	}
	else{
		cerr<<"getrusage() failed"<<endl;
	}
	
	for(int i = 0; i < NUM_TESTS/4;i++){
	  //generating random  RECORDS 
	  value = rand()%VALUE_LIMIT;
	  Event key(value, value%2, value);
	  //insert the record
	  eventSet.insert(key, value);
	}
	//memory usage snapshot
	isSuccessful = getrusage(RUSAGE_SELF,&resourceUsage);//get resource usage statistics of process till now.
	if(isSuccessful == 0){
	  cout << "RSS: "<< (memUsage = resourceUsage.ru_maxrss) << "  PF: "
	       << (numPageFaults = resourceUsage.ru_majflt) << endl; 
	}
	else{
		cerr<<"getrusage() failed"<<endl;
	}
	for(int i = 0; i < NUM_TESTS/4;i++){
	  //generating random  RECORDS 
	  value = rand()%VALUE_LIMIT;
	  Event key(value, value%2, value);
	  //insert the record
	  eventSet.insert(key, value);
	}
	//memory usage snapshot
	isSuccessful = getrusage(RUSAGE_SELF,&resourceUsage);//get resource usage statistics of process till now.
	if(isSuccessful == 0){
	  cout << "RSS: "<< (memUsage = resourceUsage.ru_maxrss) << "  PF: "
	       << (numPageFaults = resourceUsage.ru_majflt) << endl; 
	}
	else{
		cerr<<"getrusage() failed"<<endl;
	}

 	for(int i = 0;i < 2*NUM_TESTS;i++){
	  value = rand()%VALUE_LIMIT;
	  Event key(value, value%2, value);
	  pair<bool,int> findResult = eventSet.findFirst(key);//FindFirst() checker
	}

 	for(int i = 0;i < 2*NUM_TESTS;i++){
	  value = rand()%VALUE_LIMIT;
	  Event key(value, value%2, value);
	  pair<int,list<int> > findResult = eventSet.findAll(key);//FindAll() checker


	}

	isSuccessful = getrusage(RUSAGE_SELF,&resourceUsage);//get resource usage statistics of process till now.
	if(isSuccessful == 0){
	  cout << "RSS: "<< (memUsage = resourceUsage.ru_maxrss) << 
	    " PF: "<< (numPageFaults = resourceUsage.ru_majflt) << endl;
	}


 	for(int i = 0;i < 2*NUM_TESTS;i++){
		value = rand()%VALUE_LIMIT;
		Event key(value, value%2, value);
		pair<bool,int> findResult = eventSet.deleteFirst(key);//DeleteFirst() checker

	}
	isSuccessful = getrusage(RUSAGE_SELF,&resourceUsage);//get resource usage statistics of process till now.
	if(isSuccessful == 0){
	  cout << "RSS: "<< (memUsage = resourceUsage.ru_maxrss)  <<
	    " PF: "<< (numPageFaults = resourceUsage.ru_majflt) << endl;
	}


 	for(int i = 0;i < 2*NUM_TESTS;i++){
		value = rand()%VALUE_LIMIT;
		Event key(value, value%2, rand());
		pair<int,list<int> > findResult = eventSet.deleteAll(key);//DeleteAll() checker

	}
	isSuccessful = getrusage(RUSAGE_SELF,&resourceUsage);//get resource usage statistics of process till now.
	if(isSuccessful == 0){
	  cout << "RSS: "<< (memUsage = resourceUsage.ru_maxrss) <<  
	    " PF: "<< (numPageFaults = resourceUsage.ru_majflt) << endl;
	}

	cout << "Time required: " << stopTimer() << endl;
	

return 0;
}
