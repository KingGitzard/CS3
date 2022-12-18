// selecting oranges
// converting vectors to multimaps
// Mikhail Nesterenko and modified by Hunter Harbison
// 3/1/22


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <map>
#include <algorithm>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap; using std::make_pair;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

struct Fruit{
   Variety v;
   string color; // red, green or orange
};


int main(){
   srand(time(nullptr));
   multimap<Variety, string> orangeMap;
   int size = rand()%100+1;

   for(int i = 0; i<size; ++i){
       orangeMap.emplace(static_cast<Variety>(rand()%3), colors[rand()%3]);
   }
 
   cout << "Colors of the oranges: ";
   for(auto it = orangeMap.lower_bound(Variety::orange); it != orangeMap.upper_bound(Variety::orange); ++it){
        cout << it -> second << endl; 
   }
}
