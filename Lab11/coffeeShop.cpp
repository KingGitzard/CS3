//Coffee shop implementation
//Hunter Harbison
// 4/19/2022

#include "drink.hpp"
#include <iostream>
#include <string>

int main() {
    srand(time(NULL));

    char size, topping;
    string name, order;
    double price = 0.0;

    deque<ConcreteCustomer> customers;
    vector<string>orders;              // vector of a string that contains the names of the orders
	ConcreteBarista* b = new JuniorBarista(new SeniorBarista(new Manager));  // concrete barista using chain of responsibility 
	int serveDec, index = 0; // int of a random decision of the barista and an index for the deque
			 
	ConcreteCustomer c1(" ", b, nullptr), c2(" ", b, nullptr), c3(" ", b, nullptr), c4(" ", b, nullptr), c5(" ", b, nullptr); // makes 5 Concrete customer objects
	customers.push_back(c1); customers.push_back(c2); customers.push_back(c3); customers.push_back(c4); customers.push_back(c5); // pushes the customer objects into the deque

	while (!customers.empty()) { 
		 serveDec = rand() % 2 + 1;  // random decison of the barista
		Drink* d = new Drink; // the current customer's drink
		
		if (serveDec == 2 &&  !customers.empty() && index < customers.size()) { // if serveDec is 2 the barista ask a new customer for their drink
			cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee?: "; // ask user for customer's drink size
			cin >> size;
			d->setSize(size); // sets the size of the drink
			
			order = d->getOrderName(); // saves the order name of the drink
			price = d->getPrice();    // saves the price of the drink
			do {

				cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot?"; // ask the user if the customer wants toppings
				cin >> topping;
					// modifys the order name and the price using decorator design patters based on topping's character value
				if (topping == 's') { Sprinkles s(d); order += s.getName(); price += s.getPrice(); }
				if (topping == 'c') { Caramel c(d);  order += c.getName(); price += c.getPrice(); }
				if (topping == 'f') { Foam f(d); order += f.getName(); price += f.getPrice(); }
				if (topping == 'i') { Ice i(d); order += i.getName(); price += i.getPrice(); }
			} while (topping != 'n'); // exits loop if topping's value is n
			
			d->setDrinkName(order); // sets the drinks name 
			d->setPrice(price);     // sets the drinks price
			
			//cout << "drink :" << d->getOrderName() << endl;
			cout << "Can I get your name?" << endl; // ask user for name of the current customer
			cin >> name;
			
			customers[index].setName(name);		//sets name of the current positon in the deque					 
			b->registerCustomer(&customers[index]); // reisters the customer at the current position in the deque
			
			customers[index].setDrink(d);  // sets the customer drink at the current position															
			orders.push_back(order);; // pushes the order name in the vector of strings
			order = ""; // resets order
			++index; 
		}
		else { // else the barista serves the drinks that are ready
			int point = 0; // point where to deregister customer in deque
			for (auto o : orders) { // range based for going through the drinks that are made in the vector
				b->handleRequest(o);// uses chain of responsiblity to handle the drinks in the vector
				b->drinkMade(o, customers[point].getName()); // uses observer pattern to notify all the registered customers the a drink is ready
				b->deregisterCustomer(&customers[point]); // degregists the front of the deque

				customers.pop_front(); // erases the front of the deque
				//++point;
			}

			//point = 0;
			index = 0; // resets index
			orders.clear(); // clears the orders that were made
		}				
	}
	delete b; // deletes the barista pointer
}