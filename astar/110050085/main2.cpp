/****Main testing findAll ***/

#include<iostream>
#include "hashIITB.h"

using namespace std;

int main(void){

  HashIITB<int,int> testHash;
  testHash.insert(12,50);
  testHash.insert(13,1);
  testHash.insert(20,5);
  testHash.insert(23,9);
  testHash.insert(13,10);
  testHash.insert(89,16);
  testHash.insert(77,78);
  testHash.insert(12,40);
  testHash.insert(13,29);
  testHash.insert(5,56);
  testHash.insert(34,19);
  testHash.insert(38,3);
  testHash.insert(13,7);
  pair<bool,int> findResult = testHash.findFirst(12);
  cout << findResult.first << " " << findResult.second << endl;
  findResult = testHash.findFirst(77);
  cout << findResult.first << " " << findResult.second << endl;
  findResult = testHash.findFirst(50);
  cout << findResult.first << endl;
  findResult = testHash.findFirst(19);
  cout << findResult.first << endl;
  pair<int,list<int> > findResults = testHash.findAll(13);

  while (!(findResults.second).empty()) {
    cout << (findResults.second).front() << " ";
    (findResults.second).pop_front();
  }
  cout << endl;

return 0;

}
