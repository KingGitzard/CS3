// drink class to be used in Coffee Shack lab
// Mikhail Nesterenko modified by Hunter Harbison
// 4/19/2022

#include <string>
#include <list>
#include <iostream>
#include <set>
#include <deque>
#include <vector>
#ifndef DRINK_HPP_
#define DRINK_HPP_

using std::cout; using std::cin; using std::string; using std::list;
using std::deque; using std::set; using std::vector; using std::endl;
using std::size_t;

enum class DrinkType { small, medium, large };

// drink class
class Drink {
public:
     Drink(DrinkType type = DrinkType::small, int price = 0) :
        type_(type), price_(price) {} 
    virtual double getPrice() const { return price_; }; 
    virtual std::string getName() const { return name_; }
    void addTop() { ++numTops; } 
    int Tops() { return numTops; }  
    void setDrinkName(const string s) { name_ = s; }; 
    void setSize(const char s) {
        if (s == 's') { type_ = DrinkType::small; size_ = "small"; price_ = 1.00; name_ = size_ + " coffee"; }
        if (s == 'm') { type_ = DrinkType::medium; size_ = "medium"; price_ = 2.00;name_= size_ + " coffee"; }
        if (s == 'l') { type_ = DrinkType::large; size_ = "large"; price_ = 3.00; name_ = size_ + " coffee"; }
    }

    void setPrice(const double p) { price_ = p; } 
    void setName(const string n) { name_ = n; }  
    string getOrderName() { return name_; }
   
private:
    double price_;
    DrinkType type_;
    string size_; 
    string name_; 
    int numTops = 0;
};

class Sprinkles : public Drink { 
public:
    Sprinkles(Drink* d) : drink_(d) {} 

    double getPrice() const override { return  0.5; } 
    string getName() const override { 
        if (0 < drink_->Tops() ) {
            drink_->addTop();
            return  ", sprinkles";
        
        }
        else {
            drink_->addTop();
            return  " with sprinkles";
            
        }
       
    }

private:
    Drink* drink_;

};

class Caramel : public Drink {  
public:
    Caramel(Drink* d) : drink_(d){}
    double getPrice() const override { return  0.20; } 

    string getName() const override { 
        if (0 < drink_->Tops()) {
            drink_->addTop();
            return  ", carmel";
        }
        else {
            drink_->addTop();
            return" with carmel";   

        }
    }

private:
    Drink* drink_;

};

class Foam : public Drink {
public:
    Foam(Drink* d) : drink_(d) {}

    double getPrice() const override { return  0.40; }

    string getName() const override {
        if (0 < drink_->Tops()) {
            drink_->addTop();
            return  ", foam";

        }
        else {
            drink_->addTop();
            return " with foam" ; 

        }

    }

private:
    Drink* drink_; 

};
class Ice : public Drink { 
public:
    Ice(Drink* d) : drink_(d) {}
    double getPrice() const override { return  0.10; } 

    string getName() const override {  
        if (0 < drink_->Tops()) {
            drink_->addTop();
            return ", ice";
        }
        else {
            drink_->addTop(); 
            return  " with ice";   
        }
    }
private:
    Drink* drink_;  
};


//observer class
class Customer{
public:
    Customer() { cout << ""; };
    Customer(class Barista* b); 
    virtual void notify() const = 0; 
   

};

// subject class
class Barista {
public:
    void registerCustomer(Customer* c) { // inserts a customer in the set
        customers_.insert(c);
    
    }
    void deregisterCustomer(Customer* c) { // erases the customer in the set
        customers_.erase(c);
    }

    void notifyCustomers() const {
        for (auto c : customers_) {      //notifies all the customers in the set       
                c->notify();            
         }   
    }
    int getSetSize() { return customers_.size(); } // returns the size of the set
private:
    set<Customer*> customers_;

};


Customer::Customer(Barista* b) { 
    b->registerCustomer(this);
};


class ConcreteBarista; 

// concrete observer
class ConcreteCustomer: public Customer{
public:
    ConcreteCustomer(const string&, ConcreteBarista* b, Drink* d); 
    void notify() const override; 
    string orderName() { 
        return order_ ->getName(); 
    }
    ConcreteCustomer() : name_(""), order_(nullptr), b_(nullptr){}
   
    string getName() { return name_; } 
    void setName(const string name) { name_ = name; } 
    void setDrink(Drink* d) {  order_ = d; } 
private:
    string name_;
    Drink* order_;
    ConcreteBarista* b_;
};

// concrete subject
class ConcreteBarista : public Barista {
public:
    ConcreteBarista(ConcreteBarista* successor = nullptr): successor_(successor) { }
    void drinkMade(const string drink, const string customerName) {
        drinkMade_ = drink; 
        customerName_ = customerName;
        notifyCustomers();
    }
    string getDrink() { return drinkMade_; }
    string getCustomerName() { return customerName_; }

    virtual void handleRequest(const string drink) {
        if (successor_ != nullptr) {
            successor_->handleRequest(drink);
        }
        else {
            cout << "No one can make this drink" << endl;
        }
        
    }
   
  
private:
    string customerName_; 
    string drinkMade_; 
   ConcreteBarista* successor_;
  

};

class JuniorBarista :public ConcreteBarista { 
public:
    JuniorBarista(ConcreteBarista* successor = nullptr):ConcreteBarista(successor){} 

    void handleRequest(const string drink) override { 
        size_t found = drink.find("with"); 
        if (found == std::string::npos) {
            cout << "Drink prepared by the Junior Barista" << endl;

        }
        else {
            ConcreteBarista::handleRequest(drink); 
        }
    }
};

class SeniorBarista : public ConcreteBarista {
public:
    SeniorBarista( ConcreteBarista* successor = nullptr):ConcreteBarista( successor) {} 

    void handleRequest(const string drink) override{
        size_t found = drink.find("foam"); 

        if (found == std::string::npos) { 
            cout << "Drink prepared by the Senior Barista " << endl;

        }
        else {
            ConcreteBarista::handleRequest(drink); 
        }
    }

};
class Manager : public ConcreteBarista {
public:
    Manager( ConcreteBarista* successor = nullptr) :ConcreteBarista( successor) {}

    void handleRequest(const string drink)override { 
        cout << "Drink prepared by the Manager" << endl;
    }

};

ConcreteCustomer::ConcreteCustomer(const string& name, ConcreteBarista* b, Drink* d): 
    name_(name),b_(b), order_(d), Customer(static_cast<Barista*>(b)) {

}
void ConcreteCustomer::notify() const {

    if (order_ != nullptr) { 
       
        if (b_->getDrink() == order_->getOrderName() && name_ == b_->getCustomerName()) { 
            //cout << "Testing Make Drink;" << endl;                                       
            cout << name_ << ", your order Of a " << order_->getOrderName() << " is ready that will be " << order_->getPrice() << " Dollars" <<endl << endl; 
          
        }
    }
 }


#endif