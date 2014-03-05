/****Most simple main. ***/

#include<iostream>
#include "hashIITB.h"

using namespace std;

int main(void){

  HashIITB<int,int> testHash;
  testHash.insert(12,50);
  testHash.insert(13,1);
  testHash.insert(20,5);
  testHash.insert(23,9);
  testHash.insert(89,16);
  testHash.insert(77,78);
  testHash.insert(12,40);
  testHash.insert(5,56);
  testHash.insert(34,19);
  testHash.insert(38,3);
  pair<bool,int> findResult = testHash.findFirst(12);
  cout << findResult.first << " " << findResult.second << endl;
  findResult = testHash.findFirst(77);
  cout << findResult.first << " " << findResult.second << endl;
  findResult = testHash.findFirst(50);
  cout << findResult.first << endl;
  findResult = testHash.findFirst(19);
  cout << findResult.first << endl;

return 0;

}
