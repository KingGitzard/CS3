// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

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
  
                                                            
  void printAll() const{                                  //added printAll function to print name and courses per student
    cout << firstName_ << " " << lastName_ << " " ;
    for(auto& classes: course_) cout << classes << " ";
    cout << endl;
  }  
  
                                                            
   void newCourse(string course){        //add new course function added
     course_.push_back(course);
   }
   
private:
   string firstName_;
   string lastName_;
   list<string> course_;
};




// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);  
// printing a list out
void printRoster(const list<Student>& roster); 

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   list<Student> roster;
   for(int i=1; i < argc; ++i){
      readRoster(roster, argv[i]);  
   }
   printRoster(roster);

}

void readRoster(list<Student>& roster, string fileName){
   ifstream course(fileName);
   string first, last;
   string courseName = fileName;
   courseName.erase(courseName.begin()+3, courseName.end());    ///get the first three digits of file name -> course name
   while(course >> first >> last){
      string str= first + ' ' + last;
      bool check = true;
      for(auto &list : roster){
        if(list.print() == str){                                //if student exists
          check = false;                                        //add course
          list.newCourse(courseName);
          break;
          }
        }
        if(check){
          Student newStudent(first, last);                      //if student doesn't exist
          newStudent.newCourse(courseName);                     //add student and course and
          roster.push_back(newStudent);                         //add student to roster
         }
       } 
   course.close();
}

// printing a list out
void printRoster(const list<Student>& roster){
  cout << "\nStudents and Course List\n\n";
  for(const auto& student : roster){
    student.printAll();
  }
  cout << endl;
}