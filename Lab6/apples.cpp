// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko modified by Hunter Harbison
// 03/1/22


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};



int main(){
   srand(time(nullptr));
   const double minWeight = 8.;
   const double maxWeight = 3.;

   cout << "Input crate size: ";
   int size;
   cin >> size;

   vector <Apples> crate(size);

    std::generate(crate.begin(), crate.end(), [=](){Apples apple1; apple1.weight=minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight); apple1.color = rand() % 2 == 1 ? "green" : "red"; return apple1;});
   
   cout << "Enter weight to find: ";
   double toFind;
   cin >> toFind;

   // count_if()
   int cnt=std::count_if(crate.begin(), crate.end(), [=](Apples apple1){ return apple1.weight > toFind;});

   cout << "There are " << cnt << " apples heavier than " << toFind << " oz" <<  endl;

   // find_if()
   cout << "at positions ";

   auto it=crate.begin();
   do{
   it=std::find_if(++it, crate.end(), [=](Apples apple1){return apple1.weight > toFind;});
   if(it == crate.end()) break;
   cout << it - crate.begin() << " ";
   }while(it != crate.end());
   cout << endl;


   // max_element()
   double heaviest = crate[0].weight;
   auto it2 = crate.begin();
   it2 = std::max_element(crate.begin(), crate.end(), [](Apples apple1, Apples apple2){return apple1.weight < apple2.weight;});
   cout << "The heaviest apple is " << it2->weight << " oz.\n";


   // for_each() or accumulate()
   double sum = 0;
   auto total = std::accumulate(crate.begin(), crate.end(), sum, [=](double a, Apples apple) {return a + apple.weight;});
   cout << "Total apple weight is: " << total << " oz" << endl;


   // transform();
   cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;
   std::transform(crate.begin(), crate.end(), crate.begin(), [=](Apples apple){Apples apple1; apple1.weight= apple.weight+toGrow; apple1.color = apple.color; return apple1;});


   // remove_if()
   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;
   crate.erase(std::remove_if(crate.begin(), crate.end(), [=](Apples &apple){return apple.weight < minAccept;}), crate.end()); 
   cout << "removed " << size - crate.size() << " elements" << endl;


   // bubble sort, replace with sort()
   std::sort(crate.begin(), crate.end(), [=](Apples apple, Apples apple2){return apple.weight < apple2.weight;});



   // for_each() possibly
   cout << "sorted remaining apples"<< endl;
   for(const auto &e: crate) {
      e.print();
   }

}
