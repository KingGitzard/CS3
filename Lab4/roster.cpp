// vector and list algorithms
// Mikhail Nesterenko
// 3/11/2014

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(list<list<string>>& roster, string fileName);  

// printing a list out
void printRoster(const list<list<string>>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ 
      cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << endl; exit(1);
   }

   list<list<string>> roster;
   for(int i=1; i < argc; ++i){
      readRoster(roster, argv[i]);  
   }
   printRoster(roster);
}

// reading in a file of names into a list of strings
void readRoster(list<list<string>>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   string courseName = fileName;
   bool check;
   courseName.erase(courseName.begin()+3, courseName.end());    //get the first three digits of file name -> course name
   while(course >> first >> last){        
      string str= first + ' ' + last;
      check = true;
      for(auto &list : roster){ 
        if(list.front() == str){       //if list matches first+last name string template and add courseName to list
          list.push_back(courseName);                           
          check = false;
          break;
          }
        }
        if(check){
          list<string> newStudent;              //if list doesn't match adds a new student and course column
          newStudent.push_back(str);           
          newStudent.push_back(courseName);
          roster.push_back(newStudent);       
         }
       } 
   course.close();
}

// printing a list out
void printRoster(const list<list<string>>& roster){
  cout << "\nStudents and Course List\n\n";
  for(auto it = roster.begin(); it != roster.end(); ++it){
  for(auto& str : *it) cout << str << " ";
  cout << endl;
  }
  cout << endl;
}