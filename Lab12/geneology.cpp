// traversing genealogical tree using Composite and Visitors
// Mikhail Nesterenko and modified by Hunter Harbison
// 4/26/2022

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::endl;
using std::string; 
using std::vector;

class Person{ // component
public:
   Person(string firstName, Person *spouse, Person *father, Person *mother):
      firstName_(firstName), spouse_(spouse), father_(father), mother_(mother){}
   const string & getFirstName(){return firstName_;}
   Person *getSpouse(){return spouse_;}
   void setSpouse(Person *spouse){spouse_=spouse;}
   Person *getFather(){return father_;}
   Person* getMother(){return mother_;}
   virtual string getFullName()=0;
   virtual void accept(class PersonVisitor *)=0;  
   virtual ~Person(){}
private:
   const string firstName_;
   Person *spouse_;
   Person *father_;
   Person *mother_;
};


// leaf
// man has a last name 
class Man: public Person{
public:
   Man(string lastName, string firstName, Person *spouse, 
       Person *father, Person *mother): 
      lastName_(lastName), 
      Person(firstName, spouse, father, mother){}
   const string & getLastName(){return lastName_;}
   string getFullName() override{return getFirstName() + " " + getLastName();}
   void accept(class PersonVisitor *visitor) override;
private:
   const string lastName_;
};

// composite
// woman has a list of children
class Woman: public Person{
public: 
   Woman(vector<Person *> children, 
       string firstName, 
       Person *spouse, 
       Person *father, Person *mother): 
       children_(children),
       Person(firstName, spouse, father, mother){}
   const vector<Person *> & getChildren() {return children_;}
   void setChildren(const vector<Person *> &children){ children_ = children;}
   void accept(class PersonVisitor *visitor) override;
   //used to get full name in marriage class
   string getFullName() override{
        if(getSpouse() != nullptr){ return getFirstName() + " " + static_cast<Man*>(getSpouse())->getLastName();}
        if(getFather() != nullptr){ return getFirstName() + " " + static_cast<Man*>(getFather())->getLastName();}
        else return getFirstName();
    }
private:
   vector<Person *> children_;
}; 

// abstract visitor
class PersonVisitor{
public:
   virtual void visit(Man*)=0;
   virtual void visit(Woman*)=0;
   virtual ~PersonVisitor(){}
};

// composite methods that define traversal
void Man::accept(PersonVisitor *visitor) {
    visitor->visit(this);
}

void Woman::accept(PersonVisitor *visitor){ 
   // children traversal through mother only
   // father's children are not traversed so as not 
   // to traverse them twice: for mother and father

   visitor->visit(this);
   // traversing descendants
   for(auto child : children_) 
      child->accept(visitor);

   
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter: public PersonVisitor{
public:
   void visit(Man *m) override {
      cout << m->getFirstName() << " " << m->getLastName() << endl;
   }
   void visit(Woman *w) override {
      cout << w->getFirstName() << " ";
      if (w->getSpouse() != nullptr)
	 cout << static_cast<Man *> (w->getSpouse())->getLastName();
      else if (w->getFather() != nullptr)
	 cout << static_cast<Man *> (w->getFather())->getLastName();
      else
	 cout << "Doe";
      cout << endl;
   }
};


class ChildrenPrinter: public PersonVisitor{
public:
   void visit(Man *m) override {
      cout << m->getFirstName() << ": ";
      Woman *spouse = static_cast<Woman *>(m->getSpouse());
      if(spouse != nullptr)
	 printNames(spouse->getChildren());
      cout << endl;
   }
   void visit(Woman *w) override {
      cout << w->getFirstName() << ": ";
      printNames(w->getChildren());
      cout << endl;
   }
private:
   void printNames(const vector<Person *> &children){
      for(const auto c: children)
	 cout << c->getFirstName() << ", ";
   }
};

class VisitorPrinter: public PersonVisitor{
public:
  void visit(Woman *w) override {
		cout << w->getFirstName() << " ";
		cout << static_cast<Man *>(w->getFather())->getLastName() << endl;
	}
  void visit(Man *m) override {
		cout << m->getFirstName() << " " << m->getLastName() << endl;
	}
};

class MarriageAdvice: public PersonVisitor{
public:
  MarriageAdvice(std::string person1, std::string person2, int check2):p1(person1), p2(person2), check(check2){}
  int returnCheck(){return check;};
  void visit(Man *m) override{
  //voiding relationships
    if(m->getFullName() == p1 && m->getMother() != nullptr){
      for(auto e : static_cast<Woman*>(m->getMother())->getChildren()){
        if(e->getFullName() == p2){
          check=0;
          return;
        }
    }
  } 
    else if(m->getFullName() == p2 && m->getMother() != nullptr){
      for(auto e : static_cast<Woman*>(m->getMother())->getChildren()){
        if(e->getFullName() == p1){
          check=0;
          return;
        }
      }
  
    }
    if(m->getFullName() == p1 && m->getMother() != nullptr && m->getMother()->getMother() != nullptr){
      for(auto e : static_cast<Woman*>(m->getMother()->getMother())->getChildren()){
        if(e->getFullName() == p2){
          check=0;
          return;
        }
      }
  }
    else if(m->getFullName() == p1 && m->getFather() != nullptr && m->getFather()->getMother() != nullptr){
      for(auto e : static_cast<Woman*>(m->getFather()->getMother())->getChildren()){
        if(e->getFullName() == p2){
          check=0;
          return;
        }
      }
    }
  
  if(m->getFullName() == p2 && m->getMother() != nullptr && m->getMother()->getMother() != nullptr){
    for(auto e : static_cast<Woman*>(m->getMother()->getMother())->getChildren()){
      if(e->getFullName() == p1){
        check=0;
        return;
      }
    }
  }
  else if(m->getFullName() == p2 && m->getFather() != nullptr && m->getFather()->getMother() != nullptr){
    for(auto e : static_cast<Woman*>(m->getFather()->getMother())->getChildren()){
      if(e->getFullName() == p1){
        check=0;
        return;
      }
    }
  }
  if((m->getFullName() == p1 || m->getFullName() == p2) && m->getSpouse() != nullptr){
    check=0;
    return;
    }
  }


  void visit(Woman *w) override{
  // voiding relationships
    if(w->getFullName() == p1){
      for(auto e : w->getChildren()){
        if(e->getFullName() == p2){
          check=0;
          return;
        }
      }
    }
    else if(w->getFullName() == p2){
      for(auto e : w->getChildren()){
        if(e->getFullName() == p1){
          check=0;
          return;
        }
      }
    }
  if(w->getFullName() == p1 && w->getMother() != nullptr){
    for(auto e : static_cast<Woman*>(w->getMother())->getChildren()){
      if(e->getFullName() == p2){
        check=0;
        return;
      }
    }
  }
  else if(w->getFullName() == p2 && w->getMother() != nullptr){
    for(auto e : static_cast<Woman*>(w->getMother())->getChildren()){
      if(e->getFullName() == p1){
        check=0;
        return;
      }
    }
  }
  if(w->getFullName() == p1 && w->getMother() != nullptr && w->getMother()->getMother() != nullptr){
    for(auto e : static_cast<Woman*>(w->getMother()->getMother())->getChildren()){
      if(e->getFullName() == p2){
        check=0;
        return;
      }
    }
  }
  else if(w->getFullName() == p1 && w->getFather() != nullptr && w->getFather()->getMother() != nullptr){
    for(auto e : static_cast<Woman*>(w->getFather()->getMother())->getChildren()){
      if(e->getFullName() == p2){
        check=0;
        return;
      }
    }
  }
  if(w->getFullName() == p2 && w->getMother() != nullptr && w->getMother()->getMother() != nullptr){
    for(auto e : static_cast<Woman*>(w->getMother()->getMother())->getChildren()){
      if(e->getFullName() == p1){
        check=0;
        return;
      }
    }
  }
  else if(w->getFullName() == p2 && w->getFather() != nullptr && w->getFather()->getMother() != nullptr){
    for(auto e : static_cast<Woman*>(w->getFather()->getMother())->getChildren()){
      if(e->getFullName() == p1){
        check=0;
        return;
      }
    }
  }  
}

private:
  int check=1;
  std::string p1, p2;
};

// demonstrating the operation
int main(){

   // setting up the genealogical tree      
   // the tree is as follows
   //    
   //
   //       James Smith  <--spouse-->   Mary 
   //	                                  |
   //	                                 children -------------------------
   //	                                  |              |                |
   //	                                  |              |                |
   //	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
   //	                                  |
   //	                                 children------------
   //	                                  |                 |
   //                                     |                 |
   //	   Jennifer  <--spouse-->  Michael Johnson      Barbara
   //	       |
   //	     children
   //	       |
   //          |
   //	     Susan


   // first generation
   Man *js = new Man("Smith", "James", nullptr, nullptr, nullptr);
   Woman *ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
   ms->setSpouse(js); js->setSpouse(ms);

   // second generation
   Woman *ps = new Woman({}, "Patricia",  nullptr, js, ms);
   Man *wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
   ps->setSpouse(wj); wj->setSpouse(ps);

   vector<Person *> marysKids  = {ps,
			          new Man("Smith", "Robert", nullptr, js, ms),
			          new Woman({}, "Linda", nullptr, js, ms)};
   ms->setChildren(marysKids);

   // third generation
   Man *mj = new Man("Johnson", "Michael", nullptr, wj, ps);
   vector<Person *> patsKids   = {mj, new Woman({}, "Barbara", nullptr, wj, ps)}; 
   ps->setChildren(patsKids);

   Woman *jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
   vector<Person *> jensKids = {new Woman({}, "Susan", nullptr, mj ,jj)};

   jj->setSpouse(mj); mj->setSpouse(jj);
   jj->setChildren(jensKids);
   

   // defining two visitors
   ChildrenPrinter *cp = new ChildrenPrinter;
   NamePrinter *np = new NamePrinter;
   VisitorPrinter *mp = new VisitorPrinter;

   // executing the traversal with the composite
   // and the specific visitor

   cout << "\nNAME LIST\n";
   ms->accept(np);

   cout << endl << endl;

   cout << "CHILDREN LIST\n";
   ms->accept(cp);
   
   cout << "\nJAMES' CHILDREN\n";
   js->accept(cp);
   
   cout << "\nFROM PATRICIA - MAIDEN NAMES\n";
   ps->accept(mp);
   
   string firstPerson, secondPerson;
   
   cout << "\nMARRIAGE ADVICE\n";
   cout << "Enter first candidate: ";
   std::getline(std::cin, firstPerson);
   cout << "Enter second candidate: ";
   std::getline(std::cin, secondPerson);
   cout << "\n";

   int check=1;
   MarriageAdvice *ma = new MarriageAdvice(firstPerson, secondPerson, check);
   ms->accept(ma);
   check = ma->returnCheck();
   
   if(firstPerson == secondPerson) check=0;
   if(check==1) cout << "They can marry.\n";
   if(check==0) cout << "They can not marry.\n"; 
}