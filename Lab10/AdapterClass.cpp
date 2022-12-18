// figures: class adapter pattern
// Mikhail Nesterenko modified by Hunter Harbison
// 4/12/2022

#include <iostream>
#include "AdapterClass.hpp"

using std::cout; using std::endl; using std::cin;

int main(){
    int orgSize, difSize;

    cout << "Enter size for the Square: ";
    cin >> orgSize;
    Figure* square = new SquareAdapter(orgSize);
    square ->draw();
    cout <<endl;

    cout << "Enter a new size for the square: ";
    cin >> difSize;
    square -> resize(difSize);
    square -> draw();

    delete(square);
}