// hashmap implementation test
//Hunter Harbison
//3/5/2022

#include "hashmap.hpp"
#include <iostream>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string;

int main() {
  hashmap<int, string> myHash;
  auto it1 = myHash.insert(make_pair(100, "Hunter"));
  auto it2 = myHash.insert(make_pair(200, "Mikhail"));
  auto it3 = myHash.insert(make_pair(300, "Albert"));

  cout << "Testing Insert Implementation of New Employees\n\n";
  cout << "Employee 1 Key and Value: " << it1.first->first << " "<< it1.first->second << endl;
  cout << "Employee 2 Key and Value: " << it2.first->first << " "<< it2.first->second << endl;
  cout << "Employee 3 Key and Value: " << it3.first->first << " "<< it3.first->second << endl;
  
  cout << "Attemping to insert employee with used key\n";
  auto bad = myHash.insert(make_pair(100, "Patrick"));
  cout << "Bool: " << bad.second << endl;

  cout << "Testing find. Finding key 200.\n";
  auto find = myHash.find(200);
  cout << "Key 200 maps to: " << find->second << '\n';

  cout << "Testing erase. Erasing key 200.\n";
  auto erase = myHash.erase(200);
  if(erase.second) cout << "Successfully removed.\n";
 
  cout << "Testing rehash. Setting number of buckets to 10.\n";
  myHash.rehash(10);
  cout << "Testing Completed Successfully\n";
}