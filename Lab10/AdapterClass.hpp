//Hunter Harbison

#include <iostream>

#ifndef BRIDGEFIGURES_H_
#define BRIDGEFIGURES_H_


using std::cout; using std::endl;
using std::cin;
// base interface
class Figure {
public:
	virtual void draw() = 0;
	virtual void resize(int) = 0; // virtual resize
	virtual ~Figure() {}
};

// adaptee/implementer
class LegacyRectangle {
public:
	LegacyRectangle(int topLeftX,
		int topLeftY,
		int bottomRightX,
		int bottomRightY) :
		topLeftX_(topLeftX),
		topLeftY_(topLeftY),
		bottomRightX_(bottomRightX),
		bottomRightY_(bottomRightY) {}

	void oldDraw() {
		for (int i = 0; i < bottomRightY_; ++i) {
			for (int j = 0; j < bottomRightX_; ++j)
				if (i >= topLeftY_ && j >= topLeftX_)
					cout << '*';
				else
					cout << ' ';
			cout << endl;
		}
	}

	// move function that updates the cordinates
	void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
		topLeftX_ = topLeftX;
		topLeftY_ = topLeftY;
		bottomRightX_ = bottomRightX;
		bottomRightY_ = bottomRightY;
	}

	int getTopLeftX() { return topLeftX_; } // returns topLeftX_

	int getTopLeftY() { return topLeftY_; } // returns topLeftY_

	int getBottomRightX() { return bottomRightX_; } // returns bottomRightX_

	int getBottomRightY() { return bottomRightY_; } // returns bottomRightY_

	// defining top/left and bottom/right coordinates 
private:
	int topLeftX_;
	int topLeftY_;
	int bottomRightX_;
	int bottomRightY_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter : public Figure,
	private LegacyRectangle {
public:
	SquareAdapter(int size) :
		LegacyRectangle(0, 0, size, size) {};
	void draw() override {
		oldDraw();
	}

	void resize(int newSize) override{
		move(0,0,newSize,newSize);  // resizes the square by invoking move and using the parameter to increase the bottom right corner
	}

	int size() { return getBottomRightX(); } // returns BottomRightX_ by invoking getBottomRight() to get the size
};




#endif