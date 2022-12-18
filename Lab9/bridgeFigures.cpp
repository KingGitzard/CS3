// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko modified by Hunter Harbison
// 4/5/2022

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill{
public:
   Fill(char border, char inside):fillBorder_(border), fillInside_(inside){}
   virtual char getBorder()=0;
   virtual char getInternal()=0;
   virtual ~Fill() {}
protected:
   char fillBorder_;
   char fillInside_;
};

// concrete body
class Hollow: public Fill{
public:
   Hollow(char border):Fill(border, ' '){}
   char getBorder() override {return fillBorder_;}
   char getInternal() override {return fillInside_;}
   ~Hollow(){}
};


// another concrete body
class Filled: public Fill {
public:
   Filled(char inside):Fill(inside, inside){}
   char getBorder() override {return fillBorder_;}
   char getInternal() override {return fillInside_;}
   ~Filled(){}
};

// abstract handle
class Figure {
public:
   Figure(int size, Fill* fill): size_(size), fill_(fill){}
   virtual void draw() =0;
   virtual ~Figure(){}
   
   void changeFill(Fill* newFill){
      if(fill_ != nullptr) delete fill_;
	    fill_ = newFill;
    };
    
protected:
   int size_;
   Fill *fill_;
};

//new EnhancedFill concrete
class enhancedFill: public Fill {
public:
   enhancedFill(char border, char inside):Fill(border, inside){}
   char getBorder() {return fillBorder_;}
   char getInternal() {return fillInside_;}
   ~enhancedFill(){}
};

// concrete handle
class Square: public Figure{
public:
   Square(int size, Fill* fill): Figure(size, fill){}
   void draw() override;

};



void Square::draw(){
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
	 if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	    cout << fill_ -> getBorder();
	 else
	    cout << fill_ -> getInternal();
      cout << endl;
   }
}


int main(){
   // ask user for figure parameters
   cout << "Enter fill character: "; 
            char fchar; cin >> fchar;
   cout << "Filled or hollow? [f/h] "; 
           char ifFilled; cin >> ifFilled;
   cout << "Enter size: "; int size; cin >> size;

   Figure *userBox = new Square(size, ifFilled == 'f'? 
	       static_cast<Fill *>(new Filled(fchar)):
	       static_cast<Fill *>(new Hollow(fchar))
	       ); 

   userBox -> draw();
   cout << endl;
   
   //create new userBox and fill character
   cout << "Enter new fill character: ";
     char nchar; cin >> nchar;
   Figure *userBoxNew = new Square(size, static_cast<Fill *>(new enhancedFill(fchar, nchar)));
   userBoxNew -> draw();
   cout << endl;

}