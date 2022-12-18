// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move; using std::map;


class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
  string print() const {return firstName_ + ' ' + lastName_;}

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < right.firstName_);
   }
private:
   string firstName_;
   string lastName_;
};




// reading a list from a fileName
void readRoster(map<Student, list<string>>& roster, string fileName);  
// printing a list out
void printRoster(const map<Student, list<string>>& roster); 


int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   map<Student, list<string>> finalRoster;
  
   for(int i=1; i < argc; ++i){
      readRoster(finalRoster, argv[i]);  
   }
   
   printRoster(finalRoster);

}


void readRoster(map<Student, list<string>>& roster, string fileName){
  ifstream course(fileName);
  string first, last;
  string courseName = fileName;
  courseName.erase(courseName.begin()+3, courseName.end());    //gets the first three digits of file name 
  while(course >> first >> last){                              // and insterts into the course name
    auto it = roster.find(Student(first, last));
    if(it == roster.end()){
      roster.insert(std::pair<Student, list<string>>(Student(first, last), list<string>({courseName})));
      }
    else(it->second).push_back(courseName);
    } 
  course.close();
}

// printing a list out
void printRoster(const map<Student, list<string>>& roster){
 cout << "Students and Course List\n\n";
 for(auto it = roster.begin(); it != roster.end(); ++it){
    cout << (it->first).print() << " ";
    for(auto c : it->second) cout << c << ' '; 
    cout << endl;
  }
}