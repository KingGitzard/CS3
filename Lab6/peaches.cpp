// jamming peaches
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko and Hunter Harbison
// 9/30/2021


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

struct Peaches{
   double weight; // oz
   bool ripe;  // ripe or not
   void print() const { cout << (ripe?"ripe":"green") << ", " <<  weight << endl; }
};



int main(){
   srand(time(nullptr));
   const double minWeight = 8.;
   const double maxWeight = 3.;

   cout << "Input basket size: ";
   int size;
   cin >> size;

   vector <Peaches> basket(size);

   // assign random weight and ripeness peaches in the basket
   // replace with generate()
   std::generate(basket.begin(), basket.end(), [=](){Peaches peach1; peach1.weight=minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight); peach1.ripe = rand() % 2 == 1 ? "green" : "red"; return peach1;});


   
   // for_each() possibly
   cout << "all peaches"<< endl;
   for(const auto &e: basket) {
      e.print(); 
   }

   // moving all the ripe peaches from basket to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   deque<Peaches> peck;
   std::remove_copy_if(basket.begin(), basket.end(), peck.begin(), [=](Peaches peach){return peach.ripe;});
   basket.erase(std::remove_if(basket.begin(), basket.end(), [=](Peaches peach){return peach.ripe;}), basket.end());



   // for_each() possibly
   cout << "peaches remainng in the basket"<< endl;
   std::for_each(basket.begin(), basket.end(), [=](Peaches peach){if(peach.ripe)peach.print();});
   cout << endl;

   // for_each() possibly
   cout << "peaches moved to the peck"<< endl;
   std::for_each(peck.begin(), peck.end(), [=](Peaches peach){if(peach.ripe)peach.print();});



   // prints every "space" peach in the peck
   // 
   const int space=3; 
   cout << "\nevery " << space << "\'d peach in the peck"<< endl;

   // replace with advance()/next()/distance()
   // no iterator arithmetic
    int i = 1;
    auto itr = peck.begin();
    while(itr != peck.end()){
      if(itr->ripe && i%3 == 0) itr->print();
      std::advance(itr, 1);
      ++i;
   }


   // putting all small ripe peaches in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   class jam{
     public:
       jam(){};
       void operator()(vector<Peaches> peach, double max_weight){
         for(auto &e : peach){
  	       if(e.weight < max_weight) jamWeight += e.weight;
          }
       };
       
       double getJamWeight(){return jamWeight;};
     private:
       double jamWeight = 0;   
     };

   const double weightToJam = 10.0;
   jam jammie;

   auto f1 = std::bind(jammie, basket, std::placeholders::_1);
   f1(weightToJam);

   cout << "Weight of jam is: " << jammie.getJamWeight() << endl;

}
